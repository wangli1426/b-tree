#include <iostream>
#include <set>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <map>
#include "b_plus_tree.h"
#include "inner_node.h"
#include "perf_test/perf_test.cc"
#include "utility/generator.h"
int main() {
    insertion_test("test1", 2, 1000000, 1000000, 0.5);
}