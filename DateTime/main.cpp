#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString dt = QDateTime::currentDateTimeUtc().toString("yyyy:MM:dd HH:mm:ss:zzz");
    qDebug() << dt;

    return a.exec();
}
