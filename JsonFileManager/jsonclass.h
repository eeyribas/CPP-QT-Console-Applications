#ifndef JSONCLASS_H
#define JSONCLASS_H

#include <QString>
#include <QStringList>

class JsonClass
{
public:
    JsonClass();

    void SetValue1(int value);
    int GetValue1();
    void SetValue2(std::string value);
    std::string GetValue2();
    void SetValue3(int value);
    int GetValue3();
    void SetValue4(int value);
    int GetValue4();

    void Create();
    void Write();
    void Read();
    void Copy(JsonClass _json_class);

private:
    QStringList json_variables;
    std::string json_path;

    int value_1;
    std::string value_2;
    int value_3;
    int value_4;
};

#endif // JSONCLASS_H
