#include <algorithm>
#include <iostream>
#include "ReadCSV.h"
#include "DecisionTree.hpp"

int main()
{
    ReadCSV::PassagersData data = ReadCSV::readfromCSVfile("../dataset/train.csv", ReadCSV::Dataset::TRAIN);
    DecisionTree<ReadCSV::PassagerData> decision_tree(data);
    int test_head = 100;
    int correct_num = 0;
    for (int i = 0; i < test_head; ++i)
    {
        int pred = decision_tree.predict(data.at(i));
        int y = std::get<1>(data.at(i));
        std::cout << pred << ' ' << y << std::endl;
        correct_num += y == pred;
    }
    std::cout << "accuracy: [" << correct_num / test_head * 100 << "%]" << std::endl;
    return 0;
}
