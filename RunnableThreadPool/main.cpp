#include <QCoreApplication>
#include <QThreadPool>
#include <QRunnable>
#include <introduction.h>
#include <threadid.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRunnable *print_runnable = new Introduction();
    QThreadPool::globalInstance()->start(print_runnable);
    QThreadPool::globalInstance()->start(new ThreadId);

    return a.exec();
}
