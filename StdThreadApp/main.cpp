#include <QCoreApplication>
#include <iostream>
#include "process.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Process process_1;
    process_1.start(static_cast<int>(ProcessesFuncType::kMethod2), 5);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    Process process_2;
    process_2.start(static_cast<int>(ProcessesFuncType::kMethod1));
    std::this_thread::sleep_for(std::chrono::seconds(5));

    process_1.stop();
    process_2.stop();

    return a.exec();
}
