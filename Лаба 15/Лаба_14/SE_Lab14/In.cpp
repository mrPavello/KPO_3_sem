#include "stdafx.h"
#include "In.h"
#include "Error.h"
#include <fstream>

namespace In {
    //функция считывания исходного кода из файла (ключ -in:)
    IN getin(wchar_t infile[]) {
        IN input;
        input.text = new unsigned char[IN_MAX_LEN_TEXT];//массив для хранения считанного кода
        wifstream file(infile);

        if (!file.is_open()) {
            throw ERROR_THROW(110);
        }

        wchar_t current_char;//проверяемый символ
        int position = 0;//позиция в строке
        int acceptable_count = 0;//количество считанных символов

        while (file.get(current_char)) {//посимвольное чтение файла
            position++;
            input.size++;

            if (current_char >= 0 && current_char < 256) {//проверка кода сивола
                switch (input.code[current_char]) {//код символа сверяем с таблицей проверки
                case IN::T:
                    input.text[acceptable_count++] = static_cast<unsigned char>(current_char);//записываем считанны символ в массив
                    break;
                case IN::I:
                    input.ignor++;
                    input.size--;
                    break;
                case IN::F:
                    throw ERROR_THROW_IN(111, input.lines, position);
                default:
                    input.text[acceptable_count++] = static_cast<unsigned char>(input.code[current_char]);
                    break;
                }
            }
            else {
                throw ERROR_THROW_IN(111, input.lines, position);
            }

            if (current_char == IN_CODE_ENDL) {//если найден символ перехода строки, сбрасываем счетчик позиции в строке
                position = 0;
                input.lines++;
            }
        }

        file.close();
        return input;
    }
}
