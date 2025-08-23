#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    const QString DRIVER("QIBASE");
    if (QSqlDatabase::isDriverAvailable(DRIVER)) {
        printf("Found.\n");

        QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE", "firebirdDB");
        db.setConnectOptions();
        db.setHostName("192.168.1.145");
        db.setDatabaseName("//DatabaseFiles//Example.FDB");
        db.setUserName("SYSDBA");
        db.setPassword("masterkey");

        if (db.open()) {
            printf("Connected.\n");

            QStringList list;
            QSqlQuery query(db);
            query.exec("select *from communication_tb;");
            while (query.next()) {
                list.append(query.value(0).toString());
                list.append(query.value(1).toString());
                list.append(query.value(4).toString());
                qDebug() << query.value(0).toString() << "\t"
                         << query.value(1).toString() << "\t"
                         << query.value(4).toString();
            }

            qDebug() << "Disconnect.";
            db.close();
            db.removeDatabase(QSqlDatabase::defaultConnection);
        } else {
            printf("Not Connected.\n");
            qDebug() << db.lastError();
        }
    } else {
        printf("Not Found.\n");
    }

    return a.exec();
}
