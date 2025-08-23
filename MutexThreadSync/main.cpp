#include <QCoreApplication>
#include "mythread.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMutex mutex;
    int shared_var = 5;
    qDebug() << "Shared Var : " << shared_var;

    MyThread thread_1(&mutex, 1, &shared_var);
    MyThread thread_2(&mutex, 2, &shared_var);
    thread_1.start();
    thread_2.start();

    return a.exec();
}
