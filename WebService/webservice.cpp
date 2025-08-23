#include "webservice.h"

WebService::WebService()
{
    network_access_manager = new QNetworkAccessManager(this);
}

void WebService::Get(QUrl url)
{
    connect(network_access_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ReplyFinished(QNetworkReply*)));
    network_access_manager->get(QNetworkRequest(url));
}

void WebService::Post(QUrl url, QByteArray data)
{
    auto start_time = std::chrono::steady_clock::now();

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    network_access_manager->post(request, data);

    auto end_time = std::chrono::steady_clock::now();
    long time = long(std::chrono::duration_cast<std::chrono::nanoseconds>
                     (end_time - start_time).count());
    qDebug() << "Time : " << time << " nanoseconds";
}

void WebService::ReplyFinished(QNetworkReply *network_reply)
{
    qDebug() << network_reply->readAll();
}
