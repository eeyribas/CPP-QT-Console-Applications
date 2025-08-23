#include "datapaths.h"

DataPaths::DataPaths()
{
    Control();
}

void DataPaths::Control()
{
    if (!file_operations.Control(info_path))
        file_operations.Create(info_path);

    if (!file_operations.Control(exception_path))
        file_operations.Create(exception_path);
}
