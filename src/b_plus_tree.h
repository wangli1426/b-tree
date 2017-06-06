//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BPLUSTREE_H
#define B_PLUS_TREE_BPLUSTREE_H

#include <iostream>
#include "leaf_node.h"
#include "inner_node.h"
#include "node.h"

template <typename K, typename V, int CAPACITY>
class BPlusTree {
public:
    BPlusTree() {
        root_ = new LeafNode<K, V, CAPACITY>();
        depth_ = 1;
    }

    ~BPlusTree() {
        delete root_;
    }
    void insert(const K &k, const V &v) {
        Split<K, V> split;
        bool is_split;
        if (root_->is_leaf_) {
            is_split = static_cast<LeafNode<K, V, CAPACITY> *>(root_)->insert_with_split_support(k, v, split);
        } else {
            is_split = static_cast<InnerNode<K, V, CAPACITY> *>(root_)->insert_with_split_support(k, v, split);
        }
//        bool is_split = root_->insert_with_split_support(k, v, split);
        if (is_split) {
            InnerNode<K, V, CAPACITY> *new_inner_node = new InnerNode<K, V, CAPACITY>(split.left, split.right);
            root_ = new_inner_node;
            ++depth_;
        }

    }

    bool search(const K &k, V &v) const {
        return root_->search(k, v);
    }

    std::string toString() const {
        return root_->toString();
    }

private:
    Node<K, V> *root_;
    int depth_;
};

template <typename K, typename V, int CAPACITY>
std::ostream &operator<<(std::ostream &os, BPlusTree<K, V, CAPACITY> const &m) {
    return os << m.toString();
}



#endif //B_PLUS_TREE_BPLUSTREE_H
