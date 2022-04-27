#ifndef _READCSV_H_
#define _READCSV_H_

#include <vector>
#include <string>
#include <tuple>

class ReadCSV {
 public:
    enum class Sex : int {
        UNKNOWN = -1,
        FEMALE = 0,
        MALE = 1,
    };

    enum class Dataset : int {
        TRAIN = 0,
        TEST = 1,
        VALID = 2
    };

 public:
    using PassagerData = std::tuple<int,            // ID
                                    bool,           // survived
                                    int,            // pClass
                                    std::string,    // name
                                    Sex,            // sex
                                    int,            // age,parch
                                    int,            // sibsp
                                    int,            // parch
                                    std::string,    // ticket
                                    double,         // fare
                                    std::string,    // carbin
                                    char>;          // embarked
    using PassagersData = std::vector<PassagerData>;

    static PassagersData
    readfromCSVfile(const std::string &path, ReadCSV::Dataset dataset_kind, char sep = ',');

 private:
    static inline Sex sextoenum(const std::string &sex)
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
