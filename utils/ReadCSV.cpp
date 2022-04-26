#include "ReadCSV.h"

#include <fstream>
#include <stdexcept>
#include <iostream>
using namespace std;

ReadCSV::PassagersData ReadCSV::readfromCSVfile(const std::string &path, char sep)
{
    ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("file is not opened");
    string buff;
    PassagerData buff_data;
    PassagersData data;
    getline(file, buff);
    while (file.peek() && !file.eof())
    {
        getline(file, buff, sep);
        get<0>(buff_data) = buff.empty() ? -1 : stoi(buff);
        getline(file, buff, sep);
        get<1>(buff_data) = static_cast<bool>(stoi(buff));
        getline(file, buff, sep);
        get<2>(buff_data) = buff.empty() ? -1 : stoi(buff);
        getline(file, buff, sep);
        get<3>(buff_data) = buff;
        // 因为姓名栏中有逗号分隔符，所以需要读两次
        if (!buff.empty() && buff.at(0) == '"')
        {
            getline(file, buff, sep);
            get<3>(buff_data) += buff;
        }
        getline(file, buff, sep);
        get<4>(buff_data) = sextoenum(buff);
        getline(file, buff, sep);
        get<5>(buff_data) = buff.empty() ? -1 : stoi(buff);
        getline(file, buff, sep);
        get<6>(buff_data) = buff.empty() ? -1 : stoi(buff);
        getline(file, buff, sep);
        get<7>(buff_data) = buff.empty() ? -1 : stoi(buff);
        getline(file, buff, sep);
        get<8>(buff_data) = buff;
        getline(file, buff, sep);
        get<9>(buff_data) = buff.empty() ? -1.0 : stoi(buff);
        getline(file, buff, sep);
        get<10>(buff_data) = buff;
        getline(file, buff);
        get<11>(buff_data) = buff.empty() ? 0 : buff.at(0);
        data.emplace_back(buff_data);
    }
    return data;
}
