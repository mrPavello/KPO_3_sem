#include "Header.h"

int main() {
    setlocale(LC_CTYPE, "Russian");  
    char b = 'N';
    DataWithMeta item{ {"char", sizeof(char)}, b };  
    serialize("data.bin", item);  
    return 0;
}


void serialize(const std::string& filename, const DataWithMeta& item)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка при открытии файла для записи: " << filename << "\n";
        return;
    }

    size_t typeLen = item.meta.type.size();
    if (!outFile.write(reinterpret_cast<const char*>(&typeLen), sizeof(typeLen))) {
        std::cerr << "Ошибка записи длины типа в файл\n";
        return;
    }

    if (!outFile.write(item.meta.type.data(), typeLen)) {
        std::cerr << "Ошибка записи типа в файл\n";
        return;
    }

    if (!outFile.write(reinterpret_cast<const char*>(&item.meta.size), sizeof(item.meta.size))) {
        std::cerr << "Ошибка записи размера данных в файл\n";
        return;
    }

    if (!outFile.write(reinterpret_cast<const char*>(&item.data), sizeof(item.data))) {
        std::cerr << "Ошибка записи данных в файл\n";
        return;
    }

    std::cout << "Сериализация завершена успешно \n";
    outFile.close();
}
