#include <iostream>

#include "b_plus_tree.h"
#include "inner_node.h"

int main() {
    Node<int, int>* left_leaf = new LeafNode<int, int, 2>();
    Node<int, int>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(3, 3);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf, 3);

    Split<int, int> split;
    inner_node.insert_with_split_support(2, 2, split);

    inner_node.insert_with_split_support(4, 4, split);
    std::cout << inner_node.toString() << std::endl;

    inner_node.insert_with_split_support(5, 5, split);
    std::cout << inner_node.toString() << std::endl;
}