#include <iostream>
#include "ReadCSV.h"
#include "DecisionTree.h"

int main()
{
    auto data = ReadCSV::readfromCSVfile("../dataset/train.csv");
    DecisionTree decision_tree(data);
    return 0;
}
