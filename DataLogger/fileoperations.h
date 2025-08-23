#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <iostream>
#include "logger.h"

class FileOperations
{
public:
    bool Control(std::string file_path);
    void Create(std::string file_path);
    long long int Size(std::string file_path);
    void Remove(std::string file_path);
    void Write(std::string file_path, std::string text);
    void WriteWithDateInfo(std::string file_path, std::string text);
};

#endif // FILEOPERATIONS_H
