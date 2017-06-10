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
        bool is_split = root_->insert_with_split_support(k, v, split);
        if (is_split) {
            InnerNode<K, V, CAPACITY> *new_inner_node = new InnerNode<K, V, CAPACITY>(split.left, split.right);
            root_ = new_inner_node;
            ++depth_;
        }

    }

    bool delete_key(const K &k) {
        Shrink shrink;
        bool ret = root_->delete_key(k, shrink);
        if (shrink.flag && root_->type() == INNER && root_->size() == 1) {
            InnerNode<K, V, CAPACITY> *widow_inner_node = static_cast<InnerNode<K, V, CAPACITY>*>(root_);
            root_ = widow_inner_node->child_[0];
            widow_inner_node->size_ = 0;
            delete widow_inner_node;
        }
        return ret;
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
