#include <QCoreApplication>
#include <QThread>
#include <myobject.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QThread thread;
    MyObject my_object;
    my_object.DoSetup(thread);
    my_object.moveToThread(&thread);
    thread.start();

    return a.exec();
}
