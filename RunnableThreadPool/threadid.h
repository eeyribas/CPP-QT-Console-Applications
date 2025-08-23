#ifndef THREADID_H
#define THREADID_H

#include <QThreadPool>
#include <QRunnable>

class ThreadId : public QRunnable
{
public:
    ThreadId();

    void run();
};

#endif // THREADID_H
