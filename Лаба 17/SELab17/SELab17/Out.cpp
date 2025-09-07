#include "stdafx.h" 
using namespace std;

namespace Out
{

	OUT getout(wchar_t outfile[])
	{
		OUT temp; // ������� ��������� ��������� OUT
		char* outFile = new char[wcslen(outfile) + 1]; // �������� ������ ��� ����� ����� � ������� char
		wcstombs_s(NULL, outFile, wcslen(outfile) + 1, outfile, wcslen(outfile) + 1); // ����������� ��� ����� �� wchar_t � char
		temp.stream = new std::ofstream; // ������� ����� ����� ��� ������ � ����
		temp.stream->open(outFile); // ��������� ���� ��� ������
		if (!temp.stream->is_open()) // ���� ���� �� ������
		{
			ERROR_THROW(113); // ���������� ������ � ����� 113
		}
		wcscpy_s(temp.outfile, outfile); // �������� ��� ����� � ��������� OUT
		return temp; // ���������� ��������� OUT
	};

	// ������� ��� ������ ����������� � �������� ����
	void WriteOut(In::IN in, wchar_t out[])
	{
		std::ofstream fout(out); // ��������� �������� ���� ��� ������
		for (int i = 0; i < in.text.size(); i++) // ���� �� ����� ������
		{
			fout << in.text[i]; // ���������� ������ ������ � ����
		}
	};

	// ������� ��� ������ ���������� �� ������ � �������� ����
	void WriteError(OUT out, Error::ERROR error)
	{
		for (int i = 0; i < error.inext.MyVector.size(); i++) // ���� �� ��������� ������� � ����������� �� ������
		{
			*out.stream << error.inext.MyVector[i]; // ���������� ������ ������� � ����
		}
		*out.stream << endl; // ������� �� ����� ������
		*out.stream << "������" << error.id << ": " << error.message << endl << endl; // ���������� ��� � ��������� �� ������
		*out.stream << "������:" << error.inext.line << " �������:" << error.inext.col << endl << endl; // ���������� ������ � ������� ������
		if (error.inext.line != -1 && error.inext.col != -1) // ���� ������ � ������� ������ ��������
		{
			*out.stream << "������ � ������ " << ": " << error.inext.buff << endl << endl; // ���������� ������ � �������
		}
	}

	// ������� ��� �������� ��������� �����
	void Close(OUT out)
	{
		out.stream->close(); // ��������� ����
	}
}
