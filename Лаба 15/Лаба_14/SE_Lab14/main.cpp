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
        cout << "Îøèáêà " << e.id << ": " << e.message << endl << endl;
    };

    cout << endl << "TECT In::getin" << endl << endl;

    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        In::IN in = In::getin(parm.in);
        for (int i = 0; i < in.size; i++) {
            cout << in.text[i];
        }
        cout << endl;
        cout << "Âñåãî ñèìâîëîâ: " << in.size << endl;
        cout << "Âñåãî ñòðîê: " << in.lines << endl;
        cout << "Ïðîïóùåíî: " << in.ignor << endl;
    }
    catch (Error::ERROR e) {
        cout << "Îøèáêà " << e.id << ": " << e.message << endl << endl;
    };

    cout << endl;

    Log::LOG log = Log::INITLOG;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);
        
        cout << "ÒÅÑÒ Log::getlog" << endl;
        log = Log::getlog(parm.log);
        
        cout << "ÒÅÑÒ Log::WriteLine" << endl;
        Log::WriteLine(log, "Òåñò: %s", "áåç îøèáîê");
        
        cout << "ÒÅÑÒ Log::WriteLine" << endl;
        Log::WriteLine(log, L"Òåñò: %ls", L"áåç îøèáîê");
        
        cout << "ÒÅÑÒ Log::WriteLog" << endl;
        Log::WriteLog(log);
        
        cout << "ÒÅÑÒ Log::WriteParm" << endl;
        Log::WriteParm(log, parm);
        
        In::IN in = In::getin(parm.in);
        
        cout << "ÒÅÑÒ Log::WriteIn" << endl;
        Log::WriteIn(log, in);

        cout << "ÒÅÑÒ Log::Close" << endl;
        Log::Close(log);

    }
    catch (Error::ERROR e) {
        Log::WriteError(log, e);
    };

    cout << endl;

    Out::OUT out = Out::INITOUT;
    try {
        Parm::PARM parm = Parm::getparm(argc, argv);

        cout << "ÒÅÑÒ Out::getout" << endl;
        out = Out::getout(parm.out);

        In::IN in = In::getin(parm.in);
        cout << "ÒÅÑÒ Out::write_in_outfile" << endl;
        Out::write_in_outfile(out, in);

        cout << "ÒÅÑÒ Out::Close" << endl;
        Out::Close(out);
    }
    catch (Error::ERROR e) {
        Out::WriteError(out, e);
    }

    return 0;
}
