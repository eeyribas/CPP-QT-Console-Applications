#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString true_state = "T";
    QString false_state = "F";
    bool state = (false_state == "T" ? true : false);
    qDebug() << state;

    return a.exec();
}
