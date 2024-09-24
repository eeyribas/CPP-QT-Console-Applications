#include "threadid.h"
#include <QDebug>

ThreadId::ThreadId()
{
}

void ThreadId::run()
{
    for (int i = 0; i < 3; i++)
        qDebug() << QThread::currentThreadId() << " i : " << i;
}
