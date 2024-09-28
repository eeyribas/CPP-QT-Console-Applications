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
QSqlDatabase db;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t thread;
    if (pthread_create(&thread, nullptr, *DatabaseProcess, nullptr))
        perror("Thread could not be created.\n");
    usleep(1000);

    return a.exec();
}

void *DatabaseProcess(void *param)
{
    Q_UNUSED(param);

    int selected_core = 3;
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(selected_core, &cpu);
    if (sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu) == -1)
        perror("Error selected core.\n");

    printf("Database process initialized.\n");
    const QString DRIVER("QIBASE");
    if (QSqlDatabase::isDriverAvailable(DRIVER))
        printf("Driver found\n");
    else
        printf("Driver doesn't find\n");

    db = QSqlDatabase::addDatabase("QIBASE", "firebirdDB");
    db.setConnectOptions();
    db.setHostName("192.168.1.145");
    db.setDatabaseName("D:/DatabaseFiles/Shade_B.FDB");
    db.setUserName("SYSDBA");
    db.setPassword("masterkey");

    for (;;) {

        if (db.open()) {
            printf("Database connected.\n");

            QString insert_str = "select o_result from api_communication.add_('Client', '2020/06/13/11:12:15.000');";
            QSqlQuery insert_query(db);
            insert_query.exec(insert_str);
            while (insert_query.next())
                qDebug() << insert_query.value(0).toString();
            QSqlDatabase::database().commit();

            QStringList select_list;
            QSqlQuery select_query(db);
            select_query.exec("select *from communication_tb;");
            while (select_query.next()) {
                select_list.append(select_query.value(0).toString());
                select_list.append(select_query.value(1).toString());
                select_list.append(select_query.value(4).toString());
                qDebug() << select_query.value(0).toString() << "\t" << select_query.value(1).toString() << "\t" << select_query.value(4).toString();
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
