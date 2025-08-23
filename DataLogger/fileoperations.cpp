#include "fileoperations.h"
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>

bool FileOperations::Control(std::string file_path)
{
    bool result = false;
    const char* c_file_path = file_path.c_str();
    FILE* file = fopen(c_file_path, "r");
    if (file) {
        result = true;
        fclose(file);
    } else {
        result = false;
    }

    return result;
}

void FileOperations::Create(std::string file_path)
{
    std::ofstream file;
    file.open(file_path.c_str());
    file.close();
}

long long int FileOperations::Size(std::string file_path)
{
    std::ifstream f_ptr(file_path, std::ios::binary);
    f_ptr.seekg(0, std::ios::end);
    long long int file_size = f_ptr.tellg();

    return file_size;
}

void FileOperations::Remove(std::string file_path)
{
    remove(file_path.c_str());
}

void FileOperations::Write(std::string file_path, std::string text)
{
    std::ofstream f_ptr;
    f_ptr.open(file_path, std::ofstream::out | std::ofstream::app);
    if (!f_ptr.is_open()) {
        Logger::AddLog(static_cast<int>(DataLoggerType::kException),
                       "(FileOperations Class) Write() fopen failed for input file.");
    } else {
        f_ptr << text << std::endl;
    }
    f_ptr.close();
}

void FileOperations::WriteWithDateInfo(std::string file_path, std::string text)
{
    std::stringstream now_stream;
    time_t const now_time = time(nullptr);
    now_stream << std::put_time(localtime(&now_time), "%F %T");

    std::string dt = now_stream.str();
    std::string line = dt + " " + text;
    Write(file_path, line);
}
