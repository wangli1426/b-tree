//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BPLUSTREE_H
#define B_PLUS_TREE_BPLUSTREE_H

#include <iostream>
#include "leaf_node.h"
#include "inner_node.h"
#include "node.h"
#include "b_tree.h"

template<typename K, typename V, int CAPACITY>
class VanillaBPlusTree : public BTree<K, V> {
public:
    VanillaBPlusTree() {
        init();
    }

    ~VanillaBPlusTree() {
        delete root_;
    }

    void clear() {
        delete root_;
        init();
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
            InnerNode<K, V, CAPACITY> *widow_inner_node = static_cast<InnerNode<K, V, CAPACITY> *>(root_);
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

    friend std::ostream &operator<<(std::ostream &os, VanillaBPlusTree<K, V, CAPACITY> const &m) {
        return os << m.root_->toString();
    }

    typename BTree<K, V>::Iterator* get_iterator() {
        LeafNode<K, V, CAPACITY> *leftmost_leaf_node =
                dynamic_cast<LeafNode<K, V, CAPACITY> *>(root_->get_leftmost_leaf_node());
        return new Iterator(leftmost_leaf_node, 0);
    }

    typename BTree<K, V>::Iterator* range_search(const K & key_low, const K & key_high) {
        Node<K, V> *leaf_node;
        int offset;
        root_->locate_key(key_low, leaf_node, offset);
        return new Iterator(dynamic_cast<LeafNode<K, V, CAPACITY>*>(leaf_node), offset, key_high);
    };

    class Iterator: public BTree<K, V>::Iterator {
    public:
        Iterator(LeafNode<K, V, CAPACITY> *leaf_node, int offset): leaf_node_(leaf_node), offset_(offset),
                                                                   upper_bound_(false) {};
        Iterator(LeafNode<K, V, CAPACITY> *leaf_node, int offset, K key_high): leaf_node_(leaf_node), offset_(offset),
                                                                   upper_bound_(true), key_high_(key_high) {};
        virtual bool next(K & key, V & val) {
            if (!leaf_node_)
                return false;
            else if (leaf_node_->getEntry(offset_, key, val)) {
                offset_++;
                return upper_bound_ ? key < key_high_ || key == key_high_ : true;
            }
            else if (leaf_node_->right_sibling_ != 0){
                leaf_node_ = leaf_node_->right_sibling_;
                offset_ = 0;
                return next(key, val);
            } else {
                return false;
            }
        }
    private:
        LeafNode<K, V, CAPACITY> *leaf_node_;
        int offset_;
        bool upper_bound_;
        K key_high_;
    };

private:
    void init() {
        root_ = new LeafNode<K, V, CAPACITY>();
        depth_ = 1;
    }

private:
    Node<K, V> *root_;
    int depth_;
};

#endif //B_PLUS_TREE_BPLUSTREE_H
