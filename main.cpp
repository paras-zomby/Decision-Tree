#include <iostream>
#include "DecisionTree.h"

int main()
{
    ReadCSV::PassagersData data = ReadCSV::readfromCSVfile("../dataset/10-samples.csv", ReadCSV::Dataset::TRAIN);
    DecisionTree decision_tree(data);
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "predict:" << decision_tree.predict(data.at(i)) << ' '
        << "truth:" << std::get<DecisionTree::target_elem>(data.at(i)) << std::endl;
    }
    return 0;
}
