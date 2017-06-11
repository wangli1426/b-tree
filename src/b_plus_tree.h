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
    }

    ~BPlusTree() {
        delete root_;
    }

    // Insert a k-v pair to the tree.
    void insert(const K &k, const V &v) {
        Split<K, V> split;
        bool is_split;
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
        if (root_->is_leaf_) {
            is_split = static_cast<LeafNode<K, V, CAPACITY> *>(root_)->insert_with_split_support(k, v, split);
        } else {
            is_split = static_cast<InnerNode<K, V, CAPACITY> *>(root_)->insert_with_split_support(k, v, split);
        }
#else
      is_split = root_->insert_with_split_support(k, v, split);
#endif
        if (is_split) {
            InnerNode<K, V, CAPACITY> *new_inner_node = new InnerNode<K, V, CAPACITY>(split.left, split.right);
            root_ = new_inner_node;
            ++depth_;
        }

    }

    // Delete the entry from the tree. Return true if the key exists.
    bool delete_key(const K &k) {
        bool underflow;
        bool ret = root_->delete_key(k, underflow);
        if (underflow && root_->type() == INNER && root_->size() == 1) {
            InnerNode<K, V, CAPACITY> *widow_inner_node = static_cast<InnerNode<K, V, CAPACITY>*>(root_);
            root_ = widow_inner_node->child_[0];
            widow_inner_node->size_ = 0;
            delete widow_inner_node;
            --depth_;
        }
        return ret;
    }

    // Search for the value associated with the given key. If the key was found, return true and the value is stored
    // in v.
    bool search(const K &k, V &v) const {
        return root_->search(k, v);
    }

    // Return the string representation of the tree.
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
