//
// Created by Li Wang on 6/3/17.
//

#ifndef B_TREE_INNER_NODE_H
#define B_TREE_INNER_NODE_H

#include <gtest/gtest_prod.h>
#include "node.h"
template <typename K, typename V, int CAPACITY>
class InnerNode: public Node<K, V> {
    friend class InnerNodeTest;
public:
    InnerNode(): size_(0) {};
    InnerNode(Node<K, V>* left, Node<K, V>* right, K boundary) {
        size_ = 2;
        key_[0] = boundary;
        child_[0] = left;
        child_[1] = right;
    }

    bool insert(const K &key, const V &val) {
        Node<K, V>* targetNode = locateNode(key);
        return targetNode->insert(key, val);
    }

    bool point_search(const K &k, V &v) const {

    }

    bool update(const K &k, const V &v) {

    }

    bool delete_key(const K &k) {

    }

    bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) {
        Node<K, V>* target_node = locateNode(key);
        Split<K, V> local_split;
        bool splitted = target_node->insert_with_split_support(key, val, local_split);
        if (!splitted)
            return false;
    }

    std::string toString() {
        return keys_to_string() + " " + nodes_to_string();
    }

    std::string keys_to_string() {
        std::string ret = "";
        for (int i = 0; i < size_ - 1; ++i) {
            ret += std::to_string(key_[i]);
            if (i < size_ - 2)
                ret += " ";
        }
        return ret;
    }

    std::string nodes_to_string() {
        std::string ret = "";
        for (int i = 0; i < size_; ++i) {
            ret += "[" + child_[i]->toString() + "]";
            if (i != size_ - 1)
                ret += " ";
        }
        return ret;
    }

private:
//    FRIEND_TEST(InnerNodeTest, BarReturnsZeroOnNull);
    // Locate the node that might contain the particular key.
    Node<K, V>* locateNode(K key) {
        int l = 0, r = size_ - 1;
        int m;
        bool found = false;
        while(l <= r) {
            m = (l + r) / 2;
            if (key_[m] < key) {
                l = m + 1;
            } else if (key_[m] > key) {
                r = m - 1;
            } else {
                found = true;
                break;
            }
        }

        if (found) {
            return child_[m + 1];
        } else {
            return child_[l];
        }
    }

    K key_[CAPACITY - 1];
    Node<K, V>* child_[CAPACITY];
    int size_;
};

#endif //B_TREE_INNER_NODE_H
