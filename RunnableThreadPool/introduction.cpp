#include "introduction.h"
#include <QDebug>

Introduction::Introduction()
{
}

void Introduction::run()
{
    for (int i = 0; i < 3; i++)
        qDebug() << "i : " << i;
}
