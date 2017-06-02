#include "BPlusTree.h"

int main() {
    BPlusTree<int, int> tree;
    tree.insert(1,2);
    tree.insert(2,2);
    tree.insert(3,2);
//    tree.insert(4,2);
//    tree.insert(5,2);
//    tree.insert(6,2);
    std::cout << tree;
}