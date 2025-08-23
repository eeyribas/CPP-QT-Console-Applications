#include <QCoreApplication>
#include <iostream>
#include <vector>
#include "customqueue.h"
#include "data.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CustomQueue<std::vector<int>> integs_queue;
    std::vector<int> set_vec = {1, 3, 5};
    integs_queue.PutQueue(set_vec);

    CustomQueue<Data> data_queue;
    Data set_data;
    set_data.value_1 = 7;
    set_data.value_2 = true;
    set_data.value_3 = 5.6;
    data_queue.PutQueue(set_data);

    std::vector<int> get_vec = integs_queue.GetQueue();
    std::cout << "Integs Queue : ";
    for (uint i = 0; i < get_vec.size(); i++)
        std::cout << get_vec.at(i) << " ";
    std::cout << std::endl;

    Data get_data = data_queue.GetQueue();
    std::cout << "Data Queue value 1 : " << get_data.value_1
              << std::endl;
    std::cout << "Data Queue value 2 : " << get_data.value_2
              << std::endl;
    std::cout << "Data Queue value 3 : " << get_data.value_3
              << std::endl;

    return a.exec();
}
