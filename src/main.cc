#include <iostream>
#include <set>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <map>
#include "trees/vanilla_b_plus_tree.h"
#include "trees/inner_node.h"
#include "perf_test/perf_test.cc"
#include "utility/generator.h"
int main() {
//    VanillaBPlusTree<int, int, 64> bTree = VanillaBPlusTree<int, int, 64>();
//    benchmark<int, int>(&bTree, "test1", 2, 1000000, 1000000, 1000000, 1);

    VanillaBPlusTree<int, int, 4> tree;

    for (int i = 0; i < 100; i++) {
        if (i != 90)
            tree.insert(i , i);
    }

    BTree<int, int>::Iterator *it = tree.range_search(90, 96);
    int key, value;
    while(it->next(key, value)) {
        std::cout << "key: " << key << " val: " << value << std::endl;
    }

    delete it;

}