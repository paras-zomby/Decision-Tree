#ifndef _READCSV_H_
#define _READCSV_H_

#include <vector>
#include <string>
#include <tuple>

class ReadCSV {
 public:
    enum class Dataset : int {
        TRAIN = 0,
        TEST = 1,
        VALID = 2
    };

 public:
    using PassagerData = std::tuple<std::string,
                                    std::string,
                                    std::string,
                                    std::string,
                                    std::string,
                                    int>;
    using PassagersData = std::vector<PassagerData>;

    static PassagersData
    readfromCSVfile(const std::string &path, ReadCSV::Dataset dataset_kind, char sep = ',');

 private:
    static int diseasetonum(const std::string &disease);
};

#endif //_READCSV_H_
