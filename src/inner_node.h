//
// Created by Li Wang on 6/3/17.
//

#ifndef B_TREE_INNER_NODE_H
#define B_TREE_INNER_NODE_H

#include <gtest/gtest_prod.h>
#include <iostream>
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
    ~InnerNode() {
        for (int i = 0; i < size_; ++i) {
            delete child_[i];
        }
    }

    bool insert(const K &key, const V &val) {
        Node<K, V>* targetNode = child_[locate_child_index(key)];
        return targetNode->insert(key, val);
    }

    bool point_search(const K &k, V &v) const {

    }

    bool update(const K &k, const V &v) {

    }

    bool delete_key(const K &k) {

    }

    void insert_inner_node(Node<K, V> * innerNode, K boundary_key, int insert_position) {
        // Move the keys
        for (int i = size_ - 2; i >= insert_position; --i) {
            key_[i + 1] = key_[i];
        }
        // Insert the key
        key_[insert_position] = boundary_key;

        // Move the nodes
        for (int i = size_ - 1; i > insert_position; --i) {
            child_[i + 1] = child_[i];
        }
        // Insert the nodes
        child_[insert_position + 1] = innerNode;

        ++ size_;
    }

    bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) {
        int target_node_index = locate_child_index(key);
        Split<K, V> local_split;

        // Insert into the target leaf node.
        bool is_split = child_[target_node_index]->insert_with_split_support(key, val, local_split);

        // The tuple was inserted without causing leaf node to split.
        if (!is_split)
            return false;

        // The leaf node was split.
        if (size_ < CAPACITY) {
            // There is available slot in the current node for the new child.
            insert_inner_node(local_split.right, local_split.boundary_key, target_node_index);
            return false;
        }

        // leaf node was split but the current node is full. So we split the current node.
        bool insert_to_first_half = target_node_index < CAPACITY / 2;

        //
//        int boundary_key_index = (CAPACITY - 1 + insert_to_first_half) / 2 - insert_to_first_half;
        int boundary_key_index = CAPACITY / 2 - insert_to_first_half;
        InnerNode<K, V, CAPACITY> *left = this;
        InnerNode<K, V, CAPACITY> *right = new InnerNode<K, V, CAPACITY>();

        // get the boundary_key

        // move the keys to the right node;
        // all the keys greater than the boundary key belong to the right split node
        for (int i = boundary_key_index + 1, j = 0; i < size_ -1; ++i, ++j) {
            right->key_[j] = key_[i];
        }

        // move the the child;
        // all the children larger than the boundary key belong to the right split node
        for (int i = boundary_key_index + 1, j = 0; i < size_; ++i, ++j) {
            right->child_[j] = child_[i];
            ++ right->size_;
             -- left->size_;
        }

        std::cout << right->toString() << std::endl;

        // insert the right split child node.
        InnerNode<K, V, CAPACITY> *host_for_node = insert_to_first_half ? left : right;
        int inner_node_insert_position = host_for_node->locate_child_index(local_split.boundary_key);
        host_for_node->insert_inner_node(local_split.right, local_split.boundary_key, inner_node_insert_position);

        // write the remaining content in the split data structure.
        split.left = left;
        split.right = right;
        std::cout << right->toString() << std::endl;
//        split.boundary_key = right->get_leftmost_key();
        std::cout << "after: " << right->toString() << std::endl;
        return true;
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

    const K get_leftmost_key() const {
        return child_[0]->get_leftmost_key();
    }
private:
//    FRIEND_TEST(InnerNodeTest, BarReturnsZeroOnNull);
    // Locate the node that might contain the particular key.
    int locate_child_index(K key) {
        if (size_ == 0)
            return -1;
        int l = 0, r = size_ - 2;
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
            return m + 1;
        } else {
            return l;
        }
    }

    K key_[CAPACITY - 1];
    Node<K, V>* child_[CAPACITY];
    int size_;
};

#endif //B_TREE_INNER_NODE_H
