#include "ReadCSV_10.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
using namespace std;

ReadCSV::PassagersData
ReadCSV::readfromCSVfile(const std::string &path, ReadCSV::Dataset dataset_kind, char sep)
{
    ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("file is not opened");
    string buff;
    PassagerData buff_data;
    PassagersData data;
    // 扔掉header
    getline(file, buff);
    while (file.peek() && !file.eof())
    {
        getline(file, buff, sep);
        getline(file, buff, sep);
        get<0>(buff_data) = buff;
        getline(file, buff, sep);
        get<1>(buff_data) = buff;
        getline(file, buff, sep);
        get<2>(buff_data) = buff;
        getline(file, buff, sep);
        get<3>(buff_data) = buff;
        getline(file, buff, sep);
        get<4>(buff_data) = buff;
        getline(file, buff);
        get<5>(buff_data) = diseasetonum(buff);
        data.emplace_back(buff_data);
    }
    return data;
}
int ReadCSV::diseasetonum(const string &disease)
{
    if(disease == "Pneumonia\r")
        return 0;
    else if (disease == "Tuberculosis\r")
        return 1;
    else
        throw std::runtime_error("unknown disease");
}
