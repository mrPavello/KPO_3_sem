#include "stdafx.h"

using namespace std;

namespace Out
{
	OUT getout(wchar_t outfile[])
	{
		OUT file;
		file.stream = new ofstream;
		file.stream->open(outfile);

		if (file.stream->fail()) {
			throw ERROR_THROW(113);
		}

		wcscpy_s(file.outfile, outfile);
		return file;
	}


	void WriteOut(OUT out, In::IN in)
	{
		*out.stream << in.text << endl;
	}

	void WriteError(OUT log, Error::ERROR error)
	{
		*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ",позиция " << error.inext.col << std::endl;
	}

	void Close(OUT log)
	{
		log.stream->close();
		delete log.stream;
		log.stream = NULL;
	}
}

