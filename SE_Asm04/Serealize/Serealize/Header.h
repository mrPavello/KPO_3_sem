#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <locale>

struct MetaInfo {
    std::string type;
    size_t size;
};

struct DataWithMeta {
    MetaInfo meta;
    char data;
};

void serialize(const std::string& filename, const DataWithMeta& item);