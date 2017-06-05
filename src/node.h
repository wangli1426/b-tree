//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BTREENODE_H
#define B_PLUS_TREE_BTREENODE_H

#include <string>

template <typename K, typename V>
class Node;

template <typename K, typename V>
struct Split {
    Node<K, V> *left;
    Node<K, V> *right;
    K boundary_key;
};

template <typename K, typename V>
class Node{
public:
    virtual bool insert(const K &key, const V &val) = 0;
    virtual std::string toString() = 0;
    virtual bool point_search(const K &k, V &v) const = 0;
    virtual bool update(const K &k, const V &v) = 0;
    virtual bool delete_key(const K &k) = 0;
    virtual bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) = 0;
};


#endif //B_PLUS_TREE_BTREENODE_H
