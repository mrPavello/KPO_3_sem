#include <iostream>
#include "FST.h"

using namespace std;


int main() {
	setlocale(LC_ALL, "ru");
    const char* contains[] = {
        "prre",
        "prrrbcyybsxxxbsxbcrrrre",
        "prbcre",
        "prbcyre",
        "prbsxre",
        "prbsxxre",
        "prbcyyyre",
        "prrbsxxxbcyrre",
        "prrbcyysxrrer",
        "pbcyysxrre"
    };

    for (const char* contain : contains) {
        FST::FST fst1((char*)contain, 10,
            FST::NODE(1, FST::RELATION('p', 1)),
            FST::NODE(1, FST::RELATION('r', 2)),
            FST::NODE(3, FST::RELATION('r', 2), FST::RELATION('r', 8), FST::RELATION('b', 3)),
            FST::NODE(2, FST::RELATION('c', 4), FST::RELATION('s', 5)),
            FST::NODE(3, FST::RELATION('y', 6), FST::RELATION('b', 3), FST::RELATION('r', 8)),
            FST::NODE(1, FST::RELATION('x', 7)),
            FST::NODE(3, FST::RELATION('y', 6), FST::RELATION('r', 8), FST::RELATION('b', 3)),
            FST::NODE(3, FST::RELATION('x', 7), FST::RELATION('b', 3), FST::RELATION('r', 8)),
            FST::NODE(2, FST::RELATION('r', 8), FST::RELATION('e', 9)),
            FST::NODE()
        );
        if (execute(fst1)) {
            cout << "Цепочка\t" << fst1.string << "\tраспознана" << endl;
        }
        else {
            cout << "Цепочка\t" << fst1.string << "\tне распознана" << endl;
        }
    }
	

	
	

}