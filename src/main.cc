#include <iostream>
#include <set>
#include <ctime>
#include <stdlib.h>

#include "b_plus_tree.h"
#include "inner_node.h"
#include "perf_test/perf_test.cc"

int main() {
    double time  = insertion_test();
    std::cout << time << std::endl;
#ifdef MYDEFINE
    std::cout << "defined!" << std::endl;
#endif
}