#include "mythread.h"
#include <QDebug>
#include <QMutexLocker>

MyThread::MyThread(QMutex *tmp_mutex, int tmp_number,
                   int *tmp_shared_number)
{
    mutex = tmp_mutex;
    number = tmp_number;
    shared_number = tmp_shared_number;
}

void MyThread::run()
{
    qDebug() << "Thread : " << number
             << "    Shared Number : " << shared_number
             << "     * Shared Number : " << *shared_number;

    for (int i = 0; i < 5; i++) {
        mutex->lock();

        qDebug() << i << "Before Change, Number : " << number
                 << "      * Shared Number : " << *shared_number;
        (*shared_number) = number;
        usleep(10);

        if (*shared_number != number)
            qDebug() << "! collision ! at Thread : " << number;
        qDebug() << i << "After Change, Number: "<< number
                 << "      * Shared Number : " <<*shared_number;

        mutex->unlock();
        usleep(1);
    }
}
