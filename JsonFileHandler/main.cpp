#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <stdio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString file_path = "test.json";
    QStringList json_value_list = {"value1", "value2"};

    QFile file(file_path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!file.exists()) {
        qDebug() << "File not found.";
        file.close();

        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonObject json_object;
        for (int i = 0; i < json_value_list.length(); i++)
            json_object.insert(json_value_list[i], QJsonValue::fromVariant(0));

        QJsonDocument json_document;
        json_document.setObject(json_object);
        file.write(json_document.toJson());
    }
    file.close();

    int value_1 = 5;
    int value_2 = 7;
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QJsonObject write_json_object;
    write_json_object.insert(json_value_list[0], QJsonValue::fromVariant(value_1));
    write_json_object.insert(json_value_list[1], QJsonValue::fromVariant(value_2));
    QJsonDocument write_json_document;
    write_json_document.setObject(write_json_object);
    file.write(write_json_document.toJson());
    file.close();

    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString values = file.readAll();
    QJsonDocument read_json_document = QJsonDocument::fromJson(values.toUtf8());
    QJsonObject read_json_object = read_json_document.object();
    QJsonValue json_value_1 = read_json_object[json_value_list[0]];
    int json_value_int_1 = json_value_1.toInt();
    QJsonValue json_value_2 = read_json_object[json_value_list[1]];
    int json_value_int_2 = json_value_2.toInt();
    qDebug() << "Value 1 = " << json_value_int_1;
    qDebug() << "Value 2 = " << json_value_int_2;
    file.close();

    return a.exec();
}
