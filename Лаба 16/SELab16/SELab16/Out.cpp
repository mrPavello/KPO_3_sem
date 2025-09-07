#include "stdafx.h"
#include "Out.h"
#include <cstdarg>

namespace Out {
    //функция открытия или создания файла для записи
    OUT getout(wchar_t const outfile[]) {
        OUT out;
        wcsncpy_s(out.outfile, PARM_MAX_SIZE, outfile, _TRUNCATE);//копирование имени файла в структуру out

        out.stream = new ofstream(out.outfile);
        if (!out.stream->is_open()) {
            delete out.stream;
            throw ERROR_THROW(113);
        }
        return out;
    }

    //функция записывает в файл преобразованный исходный код из перваначального файла
    void write_in_outfile(OUT out, In::IN in) {
        if (out.stream && out.stream->is_open()) {
            out.stream->write(reinterpret_cast<const char*>(in.text), in.size);
        }
    }

    //вывод ошибок в файл
    void WriteError(OUT out, Error::ERROR error) {
        if (out.stream && out.stream->is_open()) {
            if (error.inext.col > 0 && error.inext.line > 0) {
                *out.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
            }
            else {
                *out.stream << "Ошибка " << error.id << ": " << error.message << std::endl;
            }
        }
        else {
            if (error.inext.col > 0 && error.inext.line > 0) {
                std::cout << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
            }
            else {
                std::cout << "Ошибка " << error.id << ": " << error.message << std::endl;
            }
        }
    }

    //закрытие файла
    void Close(OUT& out) {
        if (out.stream) {
            out.stream->close();
            delete out.stream;
            out.stream = nullptr;
        }
    }
}
