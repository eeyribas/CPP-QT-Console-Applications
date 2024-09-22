#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>

void *DatabaseProcess(void *param);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t thread;
    if (pthread_create(&thread, nullptr, *DatabaseProcess, nullptr))
        perror("Not Connected Database Control Init...\n");
    usleep(1000);

    return a.exec();
}

void *DatabaseProcess(void *param)
{
    Q_UNUSED(param);

    int selectedCore = 3;
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(selectedCore, &cpu);

    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        perror("Error Selected Core...\n");

    printf("Database Receiver Init...\n");
    const QString DRIVER("QIBASE");
    if (QSqlDatabase::isDriverAvailable(DRIVER))
        printf("Driver found.\n");
    else
        printf("Driver doesn't find.\n");

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QIBASE", "firebirdDB");
    db.setConnectOptions();
    db.setHostName("192.168.1.145");
    db.setDatabaseName("/DatabaseFiles/Example.FDB");
    db.setUserName("SYSDBA");
    db.setPassword("masterkey");

    for (;;) {

        if (db.open()) {
            printf("Database connected.\n");

            QString insert_string = "select o_result from api_communication.add_('Client', '2020/06/13/11:12:15.000');";
            QSqlQuery sql_query(db);
            sql_query.exec(insert_string);
            while (sql_query.next())
                qDebug() << sql_query.value(0).toString();
            QSqlDatabase::database().commit();

            QStringList list;
            QSqlQuery list_query(db);
            list_query.exec("select *from communication_tb;");
            while (list_query.next()) {
                list.append(list_query.value(0).toString());
                list.append(list_query.value(1).toString());
                list.append(list_query.value(4).toString());
                qDebug() << list_query.value(0).toString() << "\t" << list_query.value(1).toString() << "\t" << list_query.value(4).toString();
            }
            QSqlDatabase::database().commit();

            db.close();
        } else {
            printf("Database don't connected.\n");
            qDebug() << db.lastError();
            break;
        }

        sleep(1);
    }

    return param;
}
