#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct MetaInfo {
    std::string type;
    size_t size;
};

struct DataWithMeta {
    MetaInfo meta;
    char data;
};

DataWithMeta deserialize(const std::string& filename);
void generateAssembly(const std::string& asmFile, const DataWithMeta& item);