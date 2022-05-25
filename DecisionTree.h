#ifndef _DECISIONTREE_H_
#define _DECISIONTREE_H_

#include "ReadCSV_10.h"
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <cmath>

class DecisionTree {
 private:
    std::set<long> used_keys;
    template<typename T>
    struct _tree_node{
        int cls_depends = -1;
        int res = -1;
        std::map<T, std::pair<long, void*>> childs;
    };
 private:
    void* root = nullptr;
    long root_type = -1;

 public:
    constexpr static int target_elem = 5;

 public:
    DecisionTree() = default;
    explicit DecisionTree(const ReadCSV::PassagersData& data);

    void construct_tree(const ReadCSV::PassagersData& data);

 private:
    void new_root(long used_key);
    void construct_node(void *&ptr, long &used_key, const ReadCSV::PassagersData &data);
    
 public:
    int predict(const ReadCSV::PassagerData& data);

 private:
    template<int i, int keys>
    std::pair<long, void*> _get_child(void* ptr, const ReadCSV::PassagerData & data, long used_key)
    {
        if constexpr(i < keys)
        {
            if (used_key == i)
            {
                const std::map<typename std::tuple_element<i, ReadCSV::PassagerData>::type, std::pair<long, void*>>& childs =
                    ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->childs;
                const long& res = ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->res;
                if (res == -1)
                {
                    auto p = childs.find(std::get<i>(data));
                    if (p != childs.end())
                        return p->second;
                    else
                        return std::make_pair(-1, nullptr);
                }
                else
                    return std::make_pair(res, nullptr);
            }
            else
                return _get_child<i + 1, keys>(ptr, data, used_key);
        }
        else
            return std::make_pair(-1, nullptr);
    }
    template<int i, int keys>
    void _get_childs(void* ptr, long used_key, const std::vector<ReadCSV::PassagersData>& childs_datas)
    {
        if constexpr(i < keys)
        {
            if (i == used_key)
            {
                std::map<typename std::tuple_element<i, ReadCSV::PassagerData>::type, std::pair<long, void*>>& childs = ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->childs;
                for (auto& child: childs)
                {
                    construct_node(child.second.second, child.second.first, childs_datas[child.second.first]);
                }
            }
            else
                _get_childs<i + 1, keys>(ptr, used_key, childs_datas);
        }
    }
    inline void new_child(void *&ptr, long used_key)
    {
        _new_node<0, std::tuple_size<ReadCSV::PassagerData>::value>(ptr, used_key);
    }
    template<int i, int keys>
    void _new_node(void *&ptr, long used_key)
    {
        if constexpr(i < keys)
        {
            if (i == used_key)
            {
                ptr = (void *) new _tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>;
                ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->cls_depends = used_key;
            }
            else
                _new_node<i+1, keys>(ptr, used_key);
        }
    }
    template<int i, int keys>
    void _del_node(void *&ptr, long used_key)
    {
        if constexpr(i < keys)
        {
            if (i == used_key)
                delete (_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr;
            else
                _new_node<i+1, keys>(ptr, used_key);
        }
    }
    template<int i, int keys>
    void _set_result(void* ptr, long used_key, bool res)
    {
        if constexpr(i < keys)
        {
            if (i == used_key)
            {
                ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->res = res;
            }
            else
                _set_result<i + 1, keys>(ptr, used_key, res);
        }
    }
    template<int i, int keys>
    double _calc_ID3(const ReadCSV::PassagersData &data, long& idx)
    {
        if constexpr(i < keys)
        {
            if (data.empty())
                return 0.0;
            double id3 = 0.0;
            if (used_keys.end() == used_keys.find(i) && i != target_elem)
            {
                idx = i;
                std::map<typename std::tuple_element<i, ReadCSV::PassagerData>::type,
                         std::array<int, 2>> total;
                for (auto &passager: data)
                {
                    auto p = total.find(std::get<i>(passager));
                    if (p != total.end())
                        ++(p->second[static_cast<long>(std::get<5>(passager))]);
                    else
                        ++(total.insert(std::make_pair(std::get<i>(passager), std::array{0, 0}))
                            .first->second[static_cast<long>(std::get<5>(passager))]);
                }
                for (auto &p: total)
                {
                    double sum = p.second[0] + p.second[1];
                    id3 += sum / data.size() * -1 * (p.second[0] / sum * log2(std::max(p.second[0] / sum, 1e-6))
                                                     + (p.second[1] / sum)
                                                       * log2(std::max(p.second[1] / sum, 1e-6)));
                }
            }
            auto ret = _calc_ID3<i + 1, keys>(data, idx);
            if (ret > id3)
            {
                idx = i;
                return id3;
            }
            else
                return ret;
        }
        else
            return 0.0;
    }
    inline auto calc_ID3s(const ReadCSV::PassagersData &data)
    {
        long idx = 0;
        auto max_id3 = _calc_ID3<0, std::tuple_size<ReadCSV::PassagerData>::value>(data, idx);
        return std::make_tuple(idx, max_id3);
    }

    template<int i, int keys>
    void _diff_data(void* ptr, long used_key, const ReadCSV::PassagersData &data, std::vector<ReadCSV::PassagersData>& rets)
    {
        if constexpr(i < keys)
        {
            if (i != used_key)
                _diff_data<i + 1, keys>(ptr, used_key, data, rets);
            else
            {
                std::map<typename std::tuple_element<i, ReadCSV::PassagerData>::type, ReadCSV::PassagersData> diffed_data;
                for (auto& passager: data)
                {
                    auto p = diffed_data.find(std::get<i>(passager));
                    if (p != diffed_data.end())
                        p->second.emplace_back(passager);
                    else
                        diffed_data.insert(std::make_pair(std::get<i>(passager), ReadCSV::PassagersData{passager}));
                }
                rets.clear();
                rets.reserve(diffed_data.size());
                auto& childs = ((_tree_node<typename std::tuple_element<i, ReadCSV::PassagerData>::type>*)ptr)->childs;
                for (auto& p:diffed_data)
                {
                    //此时childs中第一个位置放孩子的key，第二个位置的第一个位置放孩子数据在所有孩子数据中的位置，
                    // 这个数据在构造孩子时会被清空，换成孩子的类型。第二个位置放孩子的指针（预留）
                    childs.insert(std::make_pair(p.first, std::make_pair(rets.size(), nullptr)));
                    rets.emplace_back(p.second);
                }
            }
        }
    }

    template<int used_key>
    bool check_if_ok(const ReadCSV::PassagersData &data)
    {
        if (data.size() <= 1)
            return true;
        else
        {
            auto key = std::get<used_key>(data[0]);
            for (int i = 1; i < data.size(); ++i)
            {
                if (key != std::get<used_key>(data[i]))
                    return false;
            }
            return true;
        }
    }

    inline void diff_node(void* p, long used_key, const ReadCSV::PassagersData &data, std::vector<ReadCSV::PassagersData>& rets)
    {
        _diff_data<0, std::tuple_size<ReadCSV::PassagerData>::value>(p, used_key, data, rets);
    }
};

#endif //_DECISIONTREE_H_
