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
    benchmark<int, int>(&bTree, "test1", 2, 1000000, 1000000, 1000000, 1);
}