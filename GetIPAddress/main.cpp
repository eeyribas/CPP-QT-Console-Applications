#include <QCoreApplication>
#include <QList>
#include <QNetworkInterface>
#include <QDebug>

QString GetIPAddress(QString network_interface)
{
    QNetworkInterface net_interface = QNetworkInterface::interfaceFromName(network_interface);
    QList<QNetworkAddressEntry> network_address_entries = net_interface.addressEntries();

    QString ip_address = "";
    if (!network_address_entries.isEmpty()) {
        QNetworkAddressEntry network_address_entry = network_address_entries.first();
        ip_address = network_address_entry.ip().toString();
    }

    return ip_address;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "Eth-0 IP Address : " << GetIPAddress("eth0");

    return a.exec();
}
