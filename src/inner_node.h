//
// Created by Li Wang on 6/3/17.
//

#ifndef B_TREE_INNER_NODE_H
#define B_TREE_INNER_NODE_H

#include <gtest/gtest_prod.h>
#include <iostream>
#include "node.h"
#include "leaf_node.h"

template <typename K, typename V, int CAPACITY>
class BPlusTree;
template <typename K, typename V, int CAPACITY>
class InnerNode: public Node<K, V> {
    friend class BPlusTree<K, V, CAPACITY>;
public:
    InnerNode(): size_(0) {
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
        this->is_leaf_ = false;
#endif
    };
    InnerNode(Node<K, V>* left, Node<K, V>* right) {
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
        this->is_leaf_ = false;
#endif
        size_ = 2;
        key_[0] = left->get_leftmost_key();
        child_[0] = left;
        key_[1] = right->get_leftmost_key();
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

    bool search(const K &k, V &v) const {
        const int index = locate_child_index(k);
        if (index < 0) return false;
        Node<K, V>* targeNode = child_[index];
        return targeNode->search(k, v);
    }

    bool update(const K &k, const V &v) {
        return true;
    }

    bool delete_key(const K &k) {

    }

    bool delete_key(const K &k, bool &underflow) {
        int child_index = locate_child_index(k);
        if (child_index < 0)
            return false;

        Node<K, V> *child = child_[child_index];
        bool deleted = child->delete_key(k, underflow);
        if (!deleted)
            return false;

        if (!underflow || size_ < 2)
            return true;


        Node<K, V> *left_child, *right_child;
        int left_child_index, right_child_index;
        int deleted_child_index = -1;
        K boundary;
        if (child_index >= 1) {
            left_child_index = child_index - 1;
            right_child_index = child_index;
        } else {
            left_child_index = child_index;
            right_child_index = child_index + 1;
        }
        left_child = child_[left_child_index];
        right_child = child_[right_child_index];


        // try to borrow a entry from the left. If no additional entry is available in the left, the two nodes will
        // be merged with the right one being deleted.
        bool merged = left_child->balance(right_child, boundary);

        if (!merged) {
            // if borrowed (not merged), update the boundary
            key_[right_child_index] = boundary;
            underflow = false;
            return true;
        }

        // merged

        // remove the reference to the deleted child, i.e., right_child
        for (int i = right_child_index; i < size_; ++i) {
            this->key_[i] = this->key_[i + 1];
            this->child_[i] = this->child_[i + 1];
        }
        --this->size_;

        underflow = this->size_ < UNDERFLOW_BOUND(CAPACITY);
        return true;
    }

    virtual bool balance(Node<K, V> *sibling_node, K &boundary) {
        const int underflow_bound = UNDERFLOW_BOUND(CAPACITY);
        InnerNode<K, V, CAPACITY> *right = static_cast<InnerNode<K, V, CAPACITY>*>(sibling_node);
        bool to_merge = false;
        if (this->size_ < underflow_bound) {
            if (right->size_ > underflow_bound) {
                // this node will borrow one child node from the right sibling node.
                this->key_[this->size_] = right->key_[0];
                this->child_[this->size_] = right->child_[0];
                ++this->size_;

                // remove the involved child in the right sibling node
                for (int  i = 0; i < right->size_; ++i) {
                    right->key_[i] = right->key_[i + 1];
                    right->child_[i] = right->child_[i + 1];
                }
                --right->size_;

                // update the boundary
                boundary = right->key_[0];
                return false;
            } else {
                to_merge = true;
            }
        }

        if (right->size_ < underflow_bound) {
            if (this->size_ > underflow_bound) {
                // make an empty slot for the entry to borrow.
                for (int i = right->size_; i >= 0; --i) {
                    right->key_[i + 1] = right->key_[i];
                    right->child_[i + 1] = right->child_[i];
                }
                ++right->size_;

                // copy the entry
                right->key_[0] = this->key_[this->size_ - 1];
                right->child_[0] = this->child_[this->size_ - 1];

                --this->size_;

                // update the boundary
                boundary = right->key_[0];
                return false;
            } else {
                to_merge = true;
            }
        }

        if (!to_merge)
            return false;

        for (int l = this->size_, r = 0; r < right->size_; ++l, ++r) {
            this->key_[l] = right->key_[r];
            this->child_[l] = right->child_[r];
        }
        this->size_ += right->size_;
        right->size_ = 0;
        delete right;
        return true;
    }

    void insert_inner_node(Node<K, V> * innerNode, K boundary_key, int insert_position) {

        // make room for insertion.
        for (int i = size_ - 1; i >= insert_position; --i) {
            key_[i + 1] = key_[i];
            child_[i + 1] = child_[i];
        }

        key_[insert_position] = boundary_key;
        child_[insert_position] = innerNode;

        ++ size_;
    }

    bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) {
        const int target_node_index = locate_child_index(key);
        const bool exceed_left_boundary = target_node_index < 0;
        Split<K, V> local_split;

        // Insert into the target leaf node.
        bool is_split;
        if (exceed_left_boundary) {
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
            if (child_[0]->is_leaf_)
                is_split = static_cast<LeafNode<K, V, CAPACITY>*>(child_[0])->insert_with_split_support(key, val, local_split);
            else
                is_split = static_cast<InnerNode<K, V, CAPACITY>*>(child_[0])->insert_with_split_support(key, val, local_split);
#else
            is_split = child_[0]->insert_with_split_support(key, val, local_split);
#endif
            key_[0] = key;
        } else {
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
            if (child_[target_node_index]->is_leaf_)
                is_split = static_cast<LeafNode<K, V, CAPACITY> *>(child_[target_node_index])->insert_with_split_support(
                        key, val, local_split);
            else
                is_split = static_cast<InnerNode<K, V, CAPACITY> *>(child_[target_node_index])->insert_with_split_support(
                        key, val, local_split);
#else
            is_split = child_[target_node_index]->insert_with_split_support(key, val, local_split);
#endif

        }

        // The tuple was inserted without causing leaf node split.
        if (!is_split)
            return false;

        // The leaf node was split.
        if (size_ < CAPACITY) {
            insert_inner_node(local_split.right, local_split.boundary_key, target_node_index + 1 + exceed_left_boundary);
            return false;
        }

        // leaf node was split but the current node is full. So we split the current node.
        bool insert_to_first_half = target_node_index < CAPACITY / 2;

        //
        int start_index_for_right = CAPACITY / 2;
        InnerNode<K, V, CAPACITY> *left = this;
        InnerNode<K, V, CAPACITY> *right = new InnerNode<K, V, CAPACITY>();

        // move the keys and children to the right node
        for (int i = start_index_for_right, j = 0; i < size_; ++i, ++j) {
            right->key_[j] = key_[i];
            right->child_[j] = child_[i];
        }

        const int moved = size_ - start_index_for_right;
        left->size_ -= moved;
        right->size_ = moved;

        // insert the new child node to the appropriate split node.
        InnerNode<K, V, CAPACITY> *host_for_node = insert_to_first_half ? left : right;
        int inner_node_insert_position = host_for_node->locate_child_index(local_split.boundary_key);
        host_for_node->insert_inner_node(local_split.right, local_split.boundary_key, inner_node_insert_position + 1);

        // write the remaining content in the split data structure.
        split.left = left;
        split.right = right;
        split.boundary_key = right->get_leftmost_key();
        return true;
    }

    std::string toString() const {
//        return std::to_string(this->id) + ": " + keys_to_string() + " " + nodes_to_string(); // for debug
        return keys_to_string() + " " + nodes_to_string();
    }

    std::string keys_to_string() const {
        std::string ret = "";
        for (int i = 1; i < size_; ++i) {
            ret += std::to_string(key_[i]);
            if (i < size_ - 1)
                ret += " ";
        }
        return ret;
    }

    std::string nodes_to_string() const {
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

    NodeType type() const {
        return INNER;
    }

    int size() const {
        return size_;
    }

protected:
    // Locate the node that might contain the particular key.
    int locate_child_index(K key) const {
#ifdef BINARY_SEARCH
        if (size_ == 0)
            return -1;
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
            return m;
        } else {
            return l -  1;
        }
#else
        // linear scan TODO: test the performance gap between binary search and linear scan.
        if (key < key_[0])
            return -1;
        int i = 1;
        while (i < size_ && key >= key_[i]) ++i;
        return i - 1;
#endif
    }

    K key_[CAPACITY]; // key_[0] is the smallest key for this inner node. The key boundaries start from index 1.
    Node<K, V>* child_[CAPACITY];
    int size_;
};

#endif //B_TREE_INNER_NODE_H
