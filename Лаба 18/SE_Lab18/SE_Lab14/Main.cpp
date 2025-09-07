#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
    setlocale(LC_ALL, "Rus");
    Log::LOG log = Log::INITLOG;
    Out::OUT out = Out::INITOUT;
    try
    {
        Parm::PARM parm = Parm::getparm(argc, argv);
        log = Log::getlog(parm.log);
        out = Out::getout(parm.out);
      
        Log::WriteLog(log);
        Log::WriteParm(log, parm);
        In::IN in = In::getin(parm.in);
        Log:WriteIn(log, in);
        Out::WriteOut(out, in);
        LT::LexTable lexTable;
        IT::IdTable	idTable;

        LEX::FindLex(in, lexTable, idTable);

        lexTable.PrintLexTable(L"Lexems.txt");
        idTable.PrintIdTable(L"Identificators.txt");

        //MFST_TRACE_START                                    // �������
          //  MFST::Mfst mfst(lexTable, GRB::getGreibach());  // �������
        //mfst.start();                                       // ����� ��������������� �������
        //mfst.savededucation();                              //  ��������� ������� ������� ������
        //mfst.printrules();                                  // ��������� ������� ������



        LT::Delete(lexTable);
        IT::Delete(idTable);
        Log::Close(log);
        Out::Close(out);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        Out::WriteError(out, e);
        cout << "������: " << e.message << " line: " << e.inext.line << " col: " << e.inext.col << endl;
    }
    system("pause");
    return 0;
}
