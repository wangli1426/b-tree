//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BTREENODE_H
#define B_PLUS_TREE_BTREENODE_H

#include <string>
template <typename K, typename V>
class Node{
public:
    virtual bool insert(const K &key, const V &val) = 0;
    virtual std::string toString() = 0;
    virtual bool point_search(const K &k, V &v) const = 0;
};
#endif //B_PLUS_TREE_BTREENODE_H
