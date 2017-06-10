//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BTREENODE_H
#define B_PLUS_TREE_BTREENODE_H

#include <string>
#include <iostream>


#define UNDERFLOW_BOUND(N) ((N + 1) / 2)

template <typename K, typename V>
class Node;

template <typename K, typename V>
struct Split {
    Node<K, V> *left;
    Node<K, V> *right;
    K boundary_key;
};

struct Shrink {
    bool flag; // shrunk or not
};

template <typename K>
struct Balance {
    bool merged;
    K boundary;
};

enum NodeType {LEAF, INNER};

static int count = 0;
template <typename K, typename V>
class Node{
public:
    Node() {
//        this->id = count++; // for debug
    }
    virtual ~Node(){
//        std::cout << id << " is deconstructed." << std::endl; // for debug
    };
    virtual bool insert(const K &key, const V &val) = 0;
    virtual std::string toString() const = 0;
    virtual bool search(const K &k, V &v) const = 0;
    virtual bool update(const K &k, const V &v) = 0;
    virtual bool delete_key(const K &k) = 0;
    virtual bool delete_key(const K &k, Shrink &shrink) = 0;
    virtual bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) = 0;
    virtual const K get_leftmost_key() const = 0;
    virtual bool balance(Node<K, V> *Sibling_node, K &boundary) = 0;
    virtual NodeType type() const = 0;
    virtual int size() const = 0;

    bool is_leaf_;
//    int id; // for debug;
};


#endif //B_PLUS_TREE_BTREENODE_H
