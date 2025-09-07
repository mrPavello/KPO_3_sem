#include "stdafx.h"
#include "Error.h" 
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"
#include "FST.h"


int _tmain(int argc, _TCHAR* argv[]) {
    setlocale(LC_ALL, "ru");
    {
        cout << "TECT Parm::getparm" << endl << endl;

        try {
            Parm::PARM parm = Parm::getparm(argc, argv);
            wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
        }
        catch (Error::ERROR e) {
            cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
        };

        cout << endl << "TECT In::getin" << endl << endl;

        try {
            Parm::PARM parm = Parm::getparm(argc, argv);
            In::IN in = In::getin(parm.in);
            for (int i = 0; i < in.size; i++) {
                cout << in.text[i];
            }
            cout << endl;
            cout << "Всего символов: " << in.size << endl;
            cout << "Всего строк: " << in.lines << endl;
            cout << "Пропущено: " << in.ignor << endl;
        }
        catch (Error::ERROR e) {
            cout << "Ошибка " << e.id << ": " << e.message << endl << endl;
        };

        cout << endl;

        Log::LOG log = Log::INITLOG;
        try {
            Parm::PARM parm = Parm::getparm(argc, argv);

            cout << "ТЕСТ Log::getlog" << endl;
            log = Log::getlog(parm.log);

            cout << "ТЕСТ Log::WriteLine" << endl;
            Log::WriteLine(log, "Тест: %s", "без ошибок");

            cout << "ТЕСТ Log::WriteLine" << endl;
            Log::WriteLine(log, L"Тест: %ls", L"без ошибок");

            cout << "ТЕСТ Log::WriteLog" << endl;
            Log::WriteLog(log);

            cout << "ТЕСТ Log::WriteParm" << endl;
            Log::WriteParm(log, parm);

            In::IN in = In::getin(parm.in);

            cout << "ТЕСТ Log::WriteIn" << endl;
            Log::WriteIn(log, in);

            cout << "ТЕСТ Log::Close" << endl;
            Log::Close(log);

        }
        catch (Error::ERROR e) {
            Log::WriteError(log, e);
        };

        cout << endl;

        Out::OUT out = Out::INITOUT;
        try {
            Parm::PARM parm = Parm::getparm(argc, argv);

            cout << "ТЕСТ Out::getout" << endl;
            out = Out::getout(parm.out);

            In::IN in = In::getin(parm.in);
            cout << "ТЕСТ Out::write_in_outfile" << endl;
            Out::write_in_outfile(out, in);

            cout << "ТЕСТ Out::Close" << endl;
            Out::Close(out);
        }
        catch (Error::ERROR e) {
            Out::WriteError(out, e);
        }
    }
    


    FST::FST fst5(
        (char*)"acebbefe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst5))  // выполнить анализ
        std::cout << "Цепочка1 " << fst5.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка1 " << fst5.string << " не распознана" << std::endl;

    FST::FST fst7(
        (char*)"abcebbfr",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()

    );

    if (FST::execute(fst7))  // выполнить анализ
        std::cout << "Цепочка2 " << fst7.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка2 " << fst7.string << " считана, но не распознана" << std::endl;

    FST::FST fst8(
        (char*)"awww",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst8))  // выполнить анализ
        std::cout << "Цепочка3 " << fst8.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка3 " << fst8.string << " не распознана" << std::endl;



    FST::FST fst9(
        (char*)"acebefe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst9))  // выполнить анализ
        std::cout << "Цепочка4 " << fst9.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка4 " << fst9.string << " не распознана" << std::endl;

    FST::FST fst10(
        (char*)"adbbbbbedbbbbbefe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst10))  // выполнить анализ
        std::cout << "Цепочка5 " << fst10.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка5 " << fst10.string << " не распознана" << std::endl;

    FST::FST fst11(
        (char*)"acebebbbfe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst11))  // выполнить анализ
        std::cout << "Цепочка6 " << fst11.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка6 " << fst11.string << " не распознана" << std::endl;

    FST::FST fst12(
        (char*)"abbbcebbbbbecebbbbbefe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst12))  // выполнить анализ
        std::cout << "Цепочка7 " << fst12.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка7 " << fst12.string << " не распознана" << std::endl;

    FST::FST fst13(
        (char*)"adbefe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst13))  // выполнить анализ
        std::cout << "Цепочка8 " << fst13.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка8 " << fst13.string << " не распознана" << std::endl;

    FST::FST fst14(
        (char*)"abbbcebbebbbfe",  // строка для распознавания
        8,            // количество состояний
        FST::NODE(1, FST::RELATION('a', 1)),
        FST::NODE(4, FST::RELATION('b', 1), FST::RELATION('b', 2), FST::RELATION('c', 2), FST::RELATION('d', 3)),
        FST::NODE(1, FST::RELATION('e', 3)),
        FST::NODE(1, FST::RELATION('b', 4)),
        FST::NODE(3, FST::RELATION('b', 4), FST::RELATION('e', 1), FST::RELATION('e', 5)),
        FST::NODE(3, FST::RELATION('b', 5), FST::RELATION('b', 6), FST::RELATION('f', 6)),
        FST::NODE(1, FST::RELATION('e', 7)),
        FST::NODE()
        // состояние 3 (конечное)
    );

    if (FST::execute(fst14))  // выполнить анализ
        std::cout << "Цепочка9 " << fst14.string << " распознана" << std::endl;
    else
        std::cout << "Цепочка9 " << fst14.string << " не распознана" << std::endl;


    return 0;
}

