#include <iostream>

#include "b_plus_tree.h"
#include "inner_node.h"

int main() {
    BPlusTree<int, int, 4> tree;
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(6, 6);


    tree.insert(10, 10);

    tree.insert(9, 9);

    tree.insert(8, 8);

    tree.insert(7, 7);
    tree.insert(4, 4);
    tree.insert(5, 5);

    tree.insert(11, 11);

    std::cout << tree.toString() << std::endl;
    tree.insert(12, 12);
    std::cout << tree.toString() << std::endl;
}