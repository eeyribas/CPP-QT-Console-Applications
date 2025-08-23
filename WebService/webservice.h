#ifndef WEBSERVICE_H
#define WEBSERVICE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class WebService : public QObject
{
    Q_OBJECT
public:
    WebService();

    void Get(QUrl url);
    void Post(QUrl url, QByteArray data);

private slots:
    void ReplyFinished(QNetworkReply *network_reply);

private:
    QNetworkAccessManager *network_access_manager;
};

#endif // WEBSERVICE_H
