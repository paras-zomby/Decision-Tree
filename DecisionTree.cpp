#include "DecisionTree.h"

#include <algorithm>
#include <stdexcept>

DecisionTree::DecisionTree(const ReadCSV::PassagersData &data)
{
    construct_tree(data);
}

void DecisionTree::construct_tree(const ReadCSV::PassagersData &data)
{
    if (check_if_ok<1>(data))
        return;
    std::vector<ReadCSV::PassagersData> childs;
    auto idx = std::get<0>(calc_ID3s(data));
    new_root(idx);
    used_keys.insert(idx);
    diff_node(root, idx, data, childs);
    _get_childs<0, std::tuple_size<ReadCSV::PassagerData>::value>(root, root_type, childs);
}

void DecisionTree::new_root(long used_key)
{
    if(root != nullptr && root_type != -1)
        _del_node<0, std::tuple_size<ReadCSV::PassagerData>::value>(root, root_type);
    root_type = used_key;
    _new_node<0, std::tuple_size<ReadCSV::PassagerData>::value>(root, used_key);
}

void DecisionTree::construct_node(void *&ptr, long &used_key, const ReadCSV::PassagersData &data)
{
    if (check_if_ok<1>(data))
    {
        _set_result<0, std::tuple_size<ReadCSV::PassagerData>::value>(ptr, used_key, std::get<1>(data.back()));
        return;
    }
    std::vector<ReadCSV::PassagersData> childs;
    used_key = std::get<0>(calc_ID3s(data));
    new_child(ptr, used_key);
    used_keys.insert(used_key);
    diff_node(root, used_key, data, childs);
    _get_childs<0, std::tuple_size<ReadCSV::PassagerData>::value>(ptr, used_key, childs);
}

bool DecisionTree::predict(const ReadCSV::TestPassagerData& data)
{
    if(root == nullptr)
        throw std::logic_error("DecisionTree::predict ERROR: cannot predict before fit");

    return false;
}
