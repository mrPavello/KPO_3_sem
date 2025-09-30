#include "Header.h"

int main() {
    setlocale(LC_CTYPE, "Russian");
    try {
        DataWithMeta item = deserialize("..\\Serealize\\data.bin");
        generateAssembly("..\\Asm\\SE_Asm04.asm", item);
        std::cout << "Ассемблерный код сгенерирован\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}




DataWithMeta deserialize(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::runtime_error("Ошибка при открытии файла для чтения");
    }
    DataWithMeta item;


    size_t typeLen;
    inFile.read(reinterpret_cast<char*>(&typeLen), sizeof(typeLen));
    item.meta.type.resize(typeLen);
    inFile.read(&item.meta.type[0], typeLen);
    inFile.read(reinterpret_cast<char*>(&item.meta.size), sizeof(item.meta.size));
    inFile.read(reinterpret_cast<char*>(&item.data), sizeof(item.data));
    inFile.close();
    return item;
}

void generateAssembly(const std::string& asmFile, const DataWithMeta& item)
{
    std::ofstream outFile(asmFile);
    if (!outFile) {
        throw std::runtime_error("Ошибка при открытии файла для записи ASM");
    }
    outFile << ".586P" << endl \
        << ".MODEL FLAT, STDCALL" << endl \
        << "includelib kernel32.lib" << endl << endl\
        << "ExitProcess PROTO : DWORD" << endl\
        << "MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD" << endl << endl\
        << ".STACK 4096" << endl << endl\
        << ".CONST" << endl << endl \
        << ".DATA" << endl << endl \
        << "MB_OK\tEQU 0" << endl\
        << "HW\t\tDD ?" << endl;
    outFile << "char DB '" << item.data << "'" << "\n";
    outFile << ".CODE" << endl << endl \
        << "main PROC" << endl << endl \
        << "START: " << endl\
        << "\tINVOKE MessageBoxA, HW, OFFSET char, OFFSET HW, MB_OK" << endl\
        << "\tpush 0" << endl \
        << "\tcall ExitProcess" << endl \
        << "main ENDP" << endl\
        << "end main" << endl;
    outFile.close();
}

