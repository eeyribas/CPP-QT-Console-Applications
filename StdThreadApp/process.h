#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

enum ProcessesFuncType
{
    kMethod1 = 0,
    kMethod2 = 1
};

class Process
{
public:
    Process();
    ~Process();
    void start(int process_type);
    void start(int process_type, int value);
    void stop();

    void Method1(int value);
    void Method2();

private:
    std::thread th;
    std::mutex mtx;
    bool state = false;
};

#endif // PROCESS_H
