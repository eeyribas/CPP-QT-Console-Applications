#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include "webservice.h"

const QUrl url(QStringLiteral("http://31.207.x.x:8889/api"));

QJsonDocument LoadJson(QString file_name)
{
    qDebug() << "Reading file.";
    QFile json_file(file_name);
    json_file.open(QFile::ReadOnly);
    QByteArray ba = json_file.readAll();

    return QJsonDocument().fromJson(ba);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    WebService web_service;

    QJsonObject json_object;
    json_object.insert("Value1", false);
    json_object.insert("Value2", "Test1");
    json_object.insert("Value3", "Test2");
    json_object.insert("Value4", 0);
    json_object.insert("Value5", 6.53);
    QJsonDocument json_document(json_object);
    QByteArray data = json_document.toJson();
    QJsonDocument json_document_file = LoadJson("Sample.json");
    QByteArray data_file = json_document_file.toJson();
    web_service.Post(url, data);

    qDebug() << "Done.";

    return a.exec();
}
