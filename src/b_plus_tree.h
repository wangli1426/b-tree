//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BPLUSTREE_H
#define B_PLUS_TREE_BPLUSTREE_H

#include <iostream>
#include "leaf_node.h"
#include "node.h"

template <typename K, typename V>
class BPlusTree {
public:
    BPlusTree() {
        root = new LeafNode<K, V, 5>();
    }
    void insert(const K &k, const V &v) {
        if (root->insert(k,v))
            std::cout << k << "," << v << " is inserted" << std::endl;
        else
            std::cout << "full!" << std::endl;
    }

    bool point_search(const K &k, V &v) const {
        return root->point_search(k, v);
    }

private:
    Node<K, V> *root;
};

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, BPlusTree<K, V> const &m) {
    return os << "content: " << m.root->toString();
}



#endif //B_PLUS_TREE_BPLUSTREE_H
