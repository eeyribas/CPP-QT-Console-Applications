#include "logger.h"

CustomQueue<std::pair<int, std::string>> Logger::data_logger_queue;

void Logger::AddLog(int logger_type, std::string log)
{
    data_logger_queue.PutQueue(std::pair<int, std::string>(logger_type, log));
}
