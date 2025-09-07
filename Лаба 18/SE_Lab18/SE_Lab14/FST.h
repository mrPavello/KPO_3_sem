#pragma once
#include "stdafx.h"
#include <cstddef>


namespace FST
{
	struct RELATION        //�����:������ -> ������� ����� ��������� ��
	{
		char symbol; // ������ ��������
		short nnode; // ����� ������� �������
		RELATION(unsigned char c = 0x00, short ns = NULL); // ������ �������� �  ����� ���������
	};

	struct NODE       // ������� ����� ���������
	{
		short n_relation;      // ���������� ����������� �����
		RELATION* relations;   // ���������� ����������� �����
		NODE();
		NODE(short n, RELATION rel, ...); // ���������� ����������� ����� � ������ �����
	};

	struct FST {               // ������������������� �������� �������
		const char* string;    // ������� (������, ���������� 0x00 )
		short position;        // ������� ������� � �������
		short nstates;         // ���������� ��������� ��������� ��������
		NODE* nodes;           // ���� ���������: [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;        // ��������� ��������� �������� �� ������ �������
		FST(const char* s, short ns, NODE n, ...); // ������� (������, ����������� 0x00 ), ���������� ��������� ��������, ������ ��������� (���� ���������)
	};

	bool execute(FST& fst); // ��������� ������������� ������� (������������������� �������� �������)
}