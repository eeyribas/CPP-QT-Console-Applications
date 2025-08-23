#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file;
    file.setFileName("test.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (file.exists()) {

        QString values = file.readAll();
        file.close();
        QJsonDocument json_document = QJsonDocument::fromJson(values.toUtf8());
        QJsonObject json_object = json_document.object();

        QJsonValue value_1 = json_object["Value1"];
        int value_int_1 = value_1.toInt();
        QJsonValue value_2 = json_object["Value2"];
        int value_int_2 = value_2.toInt();
        qDebug() << "Value1 = " << value_int_1;
        qDebug() << "Value2 = " << value_int_2;

    } else {
        qDebug() << "File not found.";
    }

    return a.exec();
}
