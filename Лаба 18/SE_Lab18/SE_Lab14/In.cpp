#include "stdafx.h" 
#include "In.h"
#include "Error.h"
#include "Out.h"
#include "Parm.h"
#include "Log.h"
#include <cstring>
#include <cstdlib>

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN in_result;
		unsigned char symbol;
		in_result.size = 0;
		in_result.ignore = 0;
		in_result.lines = 0;
		std::ifstream file;

		file.open(infile);
		if (!file.is_open())
		{
			throw ERROR_THROW(110);
		}
		in_result.text = new unsigned char[IN_MAX_LEN_TEXT];
		char* tmp = new char[IN_MAX_LEN_TEXT];

		while (file.getline(tmp, 1000))
		{
			bool lineStart = true; 
			bool prevWasSpace = false; 
			bool prevWasOperator = false;

			for (int position = 0; position < strlen(tmp); position++)
			{
				if (lineStart && tmp[position] == ' ')
				{
					in_result.ignore++;
					continue;
				}
				lineStart = false;

				if (tmp[position] == ' ' && prevWasSpace)
				{
					in_result.ignore++;
					continue;
				}

				if (tmp[position] == ' ' &&
					(isalnum(tmp[position - 1]) && isalnum(tmp[position + 1])))
				{
					if (prevWasSpace)
					{
						in_result.ignore++;
						continue;
					}
					prevWasSpace = true;
				}
				else
				{
					prevWasSpace = false;
				}

				if ((tmp[position] == ' ' && prevWasOperator) ||
					(tmp[position] == ' ' &&
						(tmp[position + 1] == '{' || tmp[position + 1] == '}' || tmp[position + 1] == '(' || tmp[position + 1] == ')' ||
							tmp[position + 1] == ';' || tmp[position + 1] == ',' || tmp[position + 1] == '+' || tmp[position + 1] == '-' ||
							tmp[position + 1] == '*' || tmp[position + 1] == '/' || tmp[position + 1] == '=')))
				{
					in_result.ignore++;
					continue;
				}

				if (tmp[position] == ' ' && tmp[position + 1] == ' ')
				{
					in_result.ignore++;
					continue;
				}

				if (tmp[position] == '{' || tmp[position] == '}' || tmp[position] == '(' || tmp[position] == ')' || tmp[position] == ';' ||
					tmp[position] == ',' || tmp[position] == '+' || tmp[position] == '-' || tmp[position] == '*' || tmp[position] == '/' || tmp[position] == '=')
				{
					prevWasOperator = true;
				}
				else
				{
					prevWasOperator = false;
				}

				switch (in_result.code[int((unsigned char)tmp[position])])
				{
				case IN::D:
					in_result.text[in_result.size++] = (unsigned)tmp[position];
					break;
				case IN::O:
					in_result.text[in_result.size++] = (unsigned)tmp[position];
					break;
				case IN::T:
					in_result.text[in_result.size++] = (unsigned)tmp[position];
					break;

				case IN::F:
					in_result.text[in_result.size] = '\0';
					throw ERROR_THROW_IN(111, in_result.lines, position + 1, in_result.text);
					break;

				case IN::I:
					in_result.ignore++;
					break;

				default:
					in_result.text[in_result.size++] = in_result.code[tmp[position]];
					break;
				}
			}
			in_result.lines++;
			in_result.text[in_result.size++] = '|';
		}
		in_result.text[in_result.size] = '\0';
		return in_result;
	}
}
