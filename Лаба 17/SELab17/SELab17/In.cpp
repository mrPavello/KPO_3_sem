#include "stdafx.h"
using namespace std;

namespace In
{
    void removeExtraSpaces(std::string& input)// Удаляем лишние пробелы из текущей строки.
    {
        bool insideQuotes = false; // Переменная для отслеживания, находимся ли мы внутри кавычек.

        for (size_t i = 0; i < input.length(); ++i) // Проходим по всем символам строки.
        {
            if (input[i] == '\'')
            {
                insideQuotes = !insideQuotes; // Если встретили одиночную кавычку, переключаем флаг.
            }
            if (!insideQuotes && input[i] == ' ') // Если это пробел и мы не внутри кавычек.
            {
                if (i == 0 || i == input.length() - 1) // Проверяем, не первый ли это или последний символ строки.
                {
                    input.erase(i, 1); // Удаляем пробел, если он в начале или в конце строки.
                }
                size_t spacesToRemove = 0; // Счётчик последовательных пробелов.
                while (i + spacesToRemove < input.length() && input[i + spacesToRemove] == ' ')
                {
                    ++spacesToRemove; // Подсчет количества последовательных пробелов после текущего символа.
                }
                if (spacesToRemove > 1) // Если больше одного пробела.
                {
                    input.erase(i + 1, spacesToRemove - 1); // Удаляем все лишние пробелы, кроме одного.
                }
            }
        }
    }

    void removeSpacesAroundOperators(std::string& input)// Удаляем пробелы вокруг операторов из текущей строки.
    {
        const std::string operators = ";,}{()=+-/*"; // Строка, содержащая все операторы, вокруг которых нужно убрать пробелы.

        for (size_t i = 0; i < input.length(); ++i) // Проходим по символам строки.
        {
            if (operators.find(input[i]) != std::string::npos) // Если текущий символ является оператором.
            {
                // Удаляем пробелы перед символом
                while (i > 0 && std::isspace(input[i - 1]))
                {
                    input.erase(i - 1, 1); // Удаляем пробел перед оператором.
                    --i; // Смещаем индекс назад, чтобы продолжить проверку.
                }

                // Удаляем пробелы после символа
                while (i + 1 < input.length() && std::isspace(input[i + 1]))
                {
                    input.erase(i + 1, 1); // Удаляем пробел после оператора.
                }
            }
        }
    }

    IN getin(wchar_t infile[]) // Функция для чтения данных из файла и их обработки.
    {
        ifstream fin; // Создаем поток для чтения файла.
        char* outFile = new char[wcslen(infile) + 1]; // Создаем буфер для имени файла в формате char.
        wcstombs_s(NULL, outFile, wcslen(infile) + 1, infile, wcslen(infile) + 1); // Преобразуем имя файла из wchar_t в char.
        fin.open(infile); // Открываем файл для чтения.
        if (fin.bad()) // Проверяем, не произошло ли ошибки при открытии файла.
        {
            throw ERROR_THROW(116); // Если ошибка, выбрасываем исключение.
        }
        if (!fin.is_open()) // Если файл не открылся.
        {
            throw ERROR_THROW(110); // Выбрасываем исключение.
        }

        IN resultIn; // Создаем структуру для хранения данных из файла.
        resultIn.size = 0; // Инициализируем начальный размер текста.
        resultIn.lines = 0; // Инициализируем количество строк.
        int position = 0; // Переменная для отслеживания позиции в строке.
        int ch; // Переменная для хранения текущего символа.
        std::string currentLine; // Строка для накопления символов.
        std::string buffer; // Буфер для считывания строк из файла.

        while (std::getline(fin, buffer)) // Считываем строку из файла.
        {
            resultIn.lines++; // Увеличиваем количество строк.
            for (int i = 0; i < buffer.length(); i++) // Проходим по символам считанной строки.
            {
                ch = buffer[i]; // Получаем текущий символ.

                if (ch == fin.eof()) // Если достигли конца файла.
                {
                    break; // Выходим из цикла.
                }

                switch (resultIn.code[(unsigned char)ch]) // Анализ символа с помощью таблицы resultIn.code.
                {
                case IN::F: // Если символ является буквой, цифрой или знаком подчеркивания, то это идентификатор.
                {
                    resultIn.text.push_back(currentLine); // Добавляем текущую строку в результат.
                    throw ERROR_THROW_IN(111, resultIn.lines, ++position, buffer, resultIn.text); // Выбрасываем исключение при ошибке.
                    break;
                }
                case IN::I: // Если символ игнорируется.
                {
                    resultIn.ignor++; // Увеличиваем счетчик игнорируемых символов.
                    position++; // Увеличиваем позицию символа в текущей строке.
                    break;
                }
                case IN::T: // Если символ является текстовым символом.
                {
                    currentLine += ch; // Добавляем символ к текущей строке.
                    position++; // Увеличиваем позицию символа в строке.
                    resultIn.size++; // Увеличиваем размер текста.
                    break;
                }
                default: // Если символ не попадает ни в одну из категорий.
                {
                    currentLine += resultIn.code[(unsigned char)ch]; // Добавляем специальный символ.
                    resultIn.size++; // Увеличиваем размер текста.
                    position++; // Увеличиваем позицию символа.
                    break;
                }
                }
            }

            if (!currentLine.empty()) // Если текущая строка не пустая.
            {
                resultIn.size++; // Увеличиваем размер текста.
                position++; // Увеличиваем позицию символа.
                position = 0; // Сбрасываем позицию после окончания строки.
                currentLine += resultIn.code[IN_CODE_ENDL]; // Добавляем символ конца строки.
                removeExtraSpaces(currentLine); // Удаляем лишние пробелы в строке.
                removeSpacesAroundOperators(currentLine); // Удаляем пробелы вокруг операторов.
                resultIn.text.push_back(currentLine); // Добавляем текущую строку в результат.
                currentLine.clear(); // Очищаем строку для следующей итерации.
            }
        }

        fin.close();
        return resultIn;
    }
}
