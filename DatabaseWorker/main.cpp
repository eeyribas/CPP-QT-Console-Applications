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
void Update(QString request);
QString Select(QString request);
QSqlDatabase db;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    pthread_t thread;
    if (pthread_create(&thread, nullptr, *DatabaseProcess, nullptr))
        perror("Thread start error occurred.\n");
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
        perror("Selected core error.\n");

    printf("Database process initialized.\n");
    const QString DRIVER("QIBASE");
    if (QSqlDatabase::isDriverAvailable(DRIVER))
        printf("Driver found.\n");
    else
        printf("Driver not find.\n");

    db = QSqlDatabase::addDatabase("QIBASE", "firebirdDB");
    db.setConnectOptions();
    db.setHostName("192.168.1.145");
    db.setDatabaseName("D:/DatabaseFiles/SHADE_READY_28_08_2020.FDB");
    db.setUserName("SYSDBA");
    db.setPassword("masterkey");

    for (;;) {
        if (db.open()) {
            printf("Database connected.\n");
            sleep(1);

            QString update_request_1 = "select * from API_PROCESS_STATEMENT.set_set_process_state('T');";
            Update(update_request_1);
            QString update_request_2 = "select * from API_PROCESS_STATEMENT.set_set_process_id('RPI RESET');";
            Update(update_request_2);
            QString update_request_3 = "select * from API_PROCESS_STATEMENT.set_get_process_state('F');";
            Update(update_request_3);
            QString update_request_4 = "select * from API_PROCESS_STATEMENT.set_get_process_id(100);";
            Update(update_request_4);

            QString select_request_1 = "select * from API_PROCESS_STATEMENT.get_set_process_state;";
            QString select_response_1 = Select(select_request_1);
            qDebug() << "Select Response - 1 = " << select_response_1;
            QString select_request_2 = "select * from API_PROCESS_STATEMENT.get_set_process_id;";
            QString select_response_2 = Select(select_request_2);
            qDebug() << "Select Response - 2 = " << select_response_2;
            QString select_request_3 = "select * from API_PROCESS_STATEMENT.get_get_process_state;";
            QString select_response_3 = Select(select_request_3);
            qDebug() << "Select Response - 3 = " << select_response_3;
            QString select_request_4 = "select * from API_PROCESS_STATEMENT.get_get_process_id;";
            QString select_response_4 = Select(select_request_4);
            qDebug() << "Select Response - 4 = " << select_response_4;

            db.close();
            printf("Database disconnected.\n");
        } else {
            printf("Database don't connected\n");
            qDebug() << db.lastError();
            break;
        }
    }

    return param;
}

void Update(QString request)
{
    QSqlQuery query(db);
    query.exec(request);
    while (query.next()){}

    QSqlDatabase::database().commit();
}

QString Select(QString request)
{
    QString response = "";

    QSqlQuery query(db);
    query.exec(request);
    while (query.next()) {
        response = query.value(0).toString();
    }

    QSqlDatabase::database().commit();

    return response;
}
