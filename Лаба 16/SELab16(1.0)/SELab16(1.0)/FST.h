#pragma once
namespace FST {
	struct RELATION {			//ребро:символ -> вершина графа переходов  ј
		char symbol;			//символ перехода
		short nnode;			//номер смежной вершины
		RELATION(
			char,		//символ перехода
			short		//новой состо€ние
		);
	};

	struct NODE {				//вершина графа преходов
		short n_relation;		//количество инцидентных ребер
		RELATION* relations;	//инцидентные ребра
		NODE();
		NODE(
			short n,			//количество инцидентных ребер
			RELATION rel, ...	//список ребер
		);
	};

	struct FST {				//недетерминированный  ј
		string string;			//цепочка (строка, завершаетс€ 0х00)
		short position;			//текуща€ позици€ в цепочке
		short nstates;			//количество состо€ний автомата
		NODE* nodes;			//граф переходов: [0] - начальное состо€ние, [nstate-1] - конечное
		short* rstates;			//возможные состо€ни€ автомата на данной позиции 
		FST(
			char* s,			//цепочка (строка, завершаетс€ 0х00)
			short ns,			//количество состо€ний автомата
			NODE n, ...			//список состо€ний (граф переходов)
		);
	};

	bool execute(				//выплнить распознавание цепочки
		FST& fst				//недетерминированный  ј
	);

	bool step(FST& fst, short*& rstates);
}