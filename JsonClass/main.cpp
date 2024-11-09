#include <QCoreApplication>
#include <iostream>
#include "jsonclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    JsonClass json_class;

    json_class.Create();
    std::cout << "Json Value 1 : " << json_class.GetValue1() << std::endl;
    std::cout << "Json Value 2 : " << json_class.GetValue2() << std::endl;
    std::cout << "Json Value 3 : " << json_class.GetValue3() << std::endl;
    std::cout << "Json Value 4 : " << json_class.GetValue4() << std::endl;

    json_class.SetValue1(15);
    json_class.SetValue2("new_value_2");
    json_class.SetValue3(21);
    json_class.SetValue4(46);
    json_class.Write();
    json_class.Read();
    std::cout << "Json Value 1 : " << json_class.GetValue1() << std::endl;
    std::cout << "Json Value 2 : " << json_class.GetValue2() << std::endl;
    std::cout << "Json Value 3 : " << json_class.GetValue3() << std::endl;
    std::cout << "Json Value 4 : " << json_class.GetValue4() << std::endl;

    JsonClass new_json_class;
    new_json_class.Copy(json_class);
    std::cout << "Json New Value 1 : " << new_json_class.GetValue1() << std::endl;
    std::cout << "Json New Value 2 : " << new_json_class.GetValue2() << std::endl;
    std::cout << "Json New Value 3 : " << new_json_class.GetValue3() << std::endl;
    std::cout << "Json New Value 4 : " << new_json_class.GetValue4() << std::endl;

    return a.exec();
}
