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
    VanillaBPlusTree<int, int, 64> bTree = VanillaBPlusTree<int, int, 64>();
    insertion_test<int, int>(&bTree, "test1", 1, 1000000, 1000000, 0.25);
}