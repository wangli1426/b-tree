//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_BTREENODE_H
#define B_PLUS_TREE_BTREENODE_H

#include <string>
#include <iostream>

#include "b_tree.h"

#define UNDERFLOW_BOUND(N) ((N + 1) / 2)

template<typename K, typename V>
class Node;

template<typename K, typename V>
class BTree;

// data structure that represents the information associated with node split
template<typename K, typename V>
struct Split {
    Node<K, V> *left;
    Node<K, V> *right;
    K boundary_key;
};

enum NodeType {
    LEAF, INNER
};

template<typename K, typename V>
class Node {
public:
    virtual ~Node() {};

    // Insert an entry (key, val) into the node. Return false if there is no room for the new entry
    virtual bool insert(const K &key, const V &val) = 0;

    // Insert an entry (key, val) into the node with split support. If the return is false, there is no split caused.
    // If the return is true, the node is split with more details available in the Split data structure.
    virtual bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) = 0;

    // Search for the value associated with the given key. Return false, if the key is not found. Otherwise, return
    // true and the value is stored in v.
    virtual bool search(const K &k, V &v) = 0;

    // Update the value associated with the given key. Return true if such a key is found. Otherwise, return false.
    virtual bool update(const K &k, const V &v) = 0;

    // Delete the entry of the given key. Return true if such a key is found. Otherwise return false. If the node is
    // under-flowed after the deletion, underflow flag will be true
    virtual bool delete_key(const K &k, bool &underflow) = 0;

    // Return the smallest key of the node
    virtual const K get_leftmost_key() const = 0;

    // This function is called when either this node or its right sibling node overflows. The underflow is solved by
    // borrowing one entry from one node to the other, if the any node has more entries than the underflow bound, or
    // merging the two nodes if otherwise. If the function returns true, the two nodes was merged and the right sibling
    // node was deleted. If the function returns false, the entries was redistributed between the two nodes and the new
    // key boundary is stored in the boundary variable.
    virtual bool balance(Node<K, V> *right_sibling_node, K &boundary) = 0;

    // Get the type of the node.
    virtual NodeType type() const = 0;

    // Get the number of entries in the leaf node or the number of children in the inner node.
    virtual int size() const = 0;

    // Return the string representation of this node.
    virtual std::string toString() const = 0;

    virtual Node* get_leftmost_leaf_node() = 0;

    virtual bool locate_key(const K &key, Node* &child, int &offset) = 0;

    // Indicate if the node is a leaf node. This flag is used to avoid the overhead of virtual function call.
#ifdef VIRTUAL_FUNCTION_OPTIMIZATION
    bool is_leaf_;
#endif
};


#endif //B_PLUS_TREE_BTREENODE_H
