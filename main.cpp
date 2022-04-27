#include <iostream>
#include "ReadCSV.h"
#include "DecisionTree.h"

int main()
{
    auto data = ReadCSV::readfromCSVfile("../dataset/train.csv");
    DecisionTree decision_tree(data);
    std::cout << decision_tree.predict(data.at(4)) << std::endl;
    std::cout << std::get<1>(data.at(4)) << std::endl;
    return 0;
}
