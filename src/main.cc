#include <iostream>

#include "b_plus_tree.h"
#include "inner_node.h"

int main() {
    Node<int, int>* left_leaf = new LeafNode<int, int, 2>();
    Node<int, int>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    left_leaf->insert(3, 3);
    right_leaf->insert(6, 6);
    right_leaf->insert(8, 8);
    InnerNode<int, int, 2> inner_node(left_leaf, right_leaf);

    Split<int, int> split;

    inner_node.insert_with_split_support(9, 9, split);
    std::cout << split.left->toString() << std::endl;
    std::cout << split.right->toString() << std::endl;
    delete split.right;
}