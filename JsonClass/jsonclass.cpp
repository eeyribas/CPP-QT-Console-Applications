#include "jsonclass.h"

JsonClass::JsonClass()
{
    json_variables.append("value_1");
    json_variables.append("value_2");
    json_variables.append("value_3");
    json_variables.append("value_4");

    json_path = "Json.json";
}

void JsonClass::SetValue1(int value) {    value_1 = value;   }
int JsonClass::GetValue1() {  return value_1; }
void JsonClass::SetValue2(std::string value) {  value_2 = value;  }
std::string JsonClass::GetValue2() { return value_2; }
void JsonClass::SetValue3(int value) {  value_3 = value;  }
int JsonClass::GetValue3(){  return value_3;   }
void JsonClass::SetValue4(int value) { value_4 = value; }
int JsonClass::GetValue4(){  return value_4;  }

void JsonClass::Create()
{
    try {
        value_1 = 0;
        value_2 = "value_2";
        value_3 = 5120;
        value_4 = 1234;

        Write();

    } catch (std::exception& e) {
    }
}

void JsonClass::Write()
{
    try {
        QFile file(QString::fromStdString(json_path));
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QJsonObject write_jo;

        write_jo.insert(json_variables[0], value_1);
        write_jo.insert(json_variables[1], QString::fromStdString(value_2));
        write_jo.insert(json_variables[2], value_3);
        write_jo.insert(json_variables[3], value_4);

        QJsonDocument write_json_doc;
        write_json_doc.setObject(write_jo);
        file.write(write_json_doc.toJson());
        file.close();

    } catch (std::exception& e) {
    }
}

void JsonClass::Read()
{
    try {
        QFile file(QString::fromStdString(json_path));
        if (file.exists()) {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QString values = file.readAll();
            if (values == "") {
                file.close();
                Create();
            } else {
                QJsonDocument read_json_doc = QJsonDocument::fromJson(values.toUtf8());
                QJsonObject read_jo = read_json_doc.object();

                QJsonValue value_1_jv = read_jo[json_variables[0]];
                QJsonValue value_2_jv = read_jo[json_variables[1]];
                QJsonValue value_3_jv = read_jo[json_variables[2]];
                QJsonValue value_4_jv = read_jo[json_variables[3]];

                value_1 = value_1_jv.toInt();
                value_2 = value_2_jv.toString().toStdString();
                value_3 = value_3_jv.toInt();
                value_4 = value_4_jv.toInt();

                file.close();

            }
        } else {
            Create();
        }

    } catch (std::exception& e) {
    }
}

void JsonClass::Copy(JsonClass _json_class)
{
    try {
        SetValue1(_json_class.GetValue1());
        SetValue2(_json_class.GetValue2());
        SetValue3(_json_class.GetValue3());
        SetValue4(_json_class.GetValue4());

    } catch (std::exception& e) {
    }
}
