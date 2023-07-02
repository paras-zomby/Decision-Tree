cmake_minimum_required(VERSION 3.21)
project(MachineLearning_DecisionTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(utils)
add_executable(MachineLearning_DecisionTree main.cpp utils/ReadCSV.cpp DecisionTree.hpp)
