#include "myobject.h"

MyObject::MyObject(QObject *parent) : QObject(parent)
{
}

void MyObject::DoSetup(QThread &thread)
{
    connect(&thread, SIGNAL(started()),
            this, SLOT(DoWork()));
}

void MyObject::DoWork()
{
    for (int i = 0; i < 10; i++)
        qDebug() << i;
}
