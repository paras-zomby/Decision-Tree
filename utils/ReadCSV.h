#ifndef _READCSV_H_
#define _READCSV_H_

#include <vector>
#include <string>
#include <tuple>

class ReadCSV {
 public:
    enum class Sex: int{
        UNKNOWN=-1,
        FEMALE=0,
        MALE=1,
    };
 private:
    struct _passager_data{
        static constexpr int class_nums = 12;
        int id;
        bool survived;
        int pclass;
        std::string name;
        Sex sex;
        int age,sibsp,parch;
        std::string ticket;
        double fare;
        std::string cabin;
        char embarked;
    };
 public:
    using PassagerData = std::tuple<int, bool, int, std::string, Sex, int, int, int, std::string, double, std::string, char>;
    using PassagersData = std::vector<PassagerData>;
    using TestPassagerData = std::tuple<int, int, std::string, Sex, int, int, int, std::string, double, std::string, char>;
    using TestPassagersData = std::vector<TestPassagerData>;

    static PassagersData readfromCSVfile(const std::string& path, char sep = ',');

 private:
    static inline Sex sextoenum(const std::string& sex)
    {
        if (sex == "male")
            return Sex::MALE;
        else if (sex == "female")
            return Sex::FEMALE;
        else
            return Sex::UNKNOWN;
    }
};

#endif //_READCSV_H_
