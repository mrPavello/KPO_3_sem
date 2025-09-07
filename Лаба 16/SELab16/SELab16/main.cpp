#include "stdafx.h"
#include "Error.h" 
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "Out.h"



int _tmain(int argc, _TCHAR* argv[]) {
    setlocale(LC_ALL, "ru");

    cout << "TECT Parm::getparm" << endl << endl;
    
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << endl << endl;
    }
    catch (Error::ERROR e) {
        cout << "������ " << e.id << ": " << e.message << endl << endl;
    };

    cout << endl << "TECT In::getin" << endl << endl;

    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN in = In::getin(parm.in);
        for (int i = 0; i < in.size; i++) {
            cout << in.text[i];
        }
        cout << endl;
        cout << "����� ��������: " << in.size << endl;
        cout << "����� �����: " << in.lines << endl;
        cout << "���������: " << in.ignor << endl;
    }
    catch (Error::ERROR e) {
        cout << "������ " << e.id << ": " << e.message << endl << endl;
    };

    cout << endl;

    Log::LOG log = Log::INITLOG;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        
        cout << "���� Log::getlog" << endl;
        log = Log::getlog(parm.log);
        
        cout << "���� Log::WriteLine" << endl;
        Log::WriteLine(log, "����: %s", "��� ������");
        
        cout << "���� Log::WriteLine" << endl;
        Log::WriteLine(log, L"����: %ls", L"��� ������");
        
        cout << "���� Log::WriteLog" << endl;
        Log::WriteLog(log);
        
        cout << "���� Log::WriteParm" << endl;
        Log::WriteParm(log, parm);
        
        In::IN in = In::getin(parm.in);
        
        cout << "���� Log::WriteIn" << endl;
        Log::WriteIn(log, in);

        cout << "���� Log::Close" << endl;
        Log::Close(log);

    }
    catch (Error::ERROR e) {
        Log::WriteError(log, e);
    };

    cout << endl;

    Out::OUT out = Out::INITOUT;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);

        cout << "���� Out::getout" << endl;
        out = Out::getout(parm.out);

        In::IN in = In::getin(parm.in);
        cout << "���� Out::write_in_outfile" << endl;
        Out::write_in_outfile(out, in);

        cout << "���� Out::Close" << endl;
        Out::Close(out);
    }
    catch (Error::ERROR e) {
        Out::WriteError(out, e);
    }

    return 0;
}
