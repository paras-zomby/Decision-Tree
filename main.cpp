#include <iostream>
#include "ReadCSV.h"
#include "DecisionTree.h"

int main()
{
    ReadCSV::PassagersData data = ReadCSV::readfromCSVfile("../dataset/train.csv", ReadCSV::Dataset::TRAIN);
    DecisionTree decision_tree(data);
    for (int i = 0; i < 100; ++i)
    {
        std::cout << decision_tree.predict(data.at(i)) << ' ' << std::get<1>(data.at(i)) << std::endl;
    }
    return 0;
}
