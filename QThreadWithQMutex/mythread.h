#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QtCore>
#include <QMutex>

class MyThread : public QThread
{
public:
    MyThread(QMutex *tmp_mutex, int tmp_number, int *tmp_shared_number);

    int number;
    int *shared_number;

protected:
    void run();

private:
    QMutex *mutex;
};

#endif // MYTHREAD_H
