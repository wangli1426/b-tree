#include <iostream>
#include <set>
#include <ctime>
#include <malloc.h>

#include "b_plus_tree.h"
#include "inner_node.h"

int main() {
    std::set<int> s;
    BPlusTree<int, int, 16> tree;
    const size_t n_tuples = 1000000;
    const size_t range = n_tuples * 10;
    int* tuples = (int*) malloc(n_tuples * sizeof(int));

    for (size_t i = 0; i < n_tuples; ++i) {
        tuples[i] = (int)(std::rand() % range);
    }



    clock_t begin = clock();

    for (int i = 0; i < n_tuples; ++i) {
        tree.insert(tuples[i], tuples[i]);
    }

    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    int value;
    std::cout << "inserted " << n_tuples << " tuples" << std::endl;
    std::cout << n_tuples / elapsed_secs << " insertions / s" <<std::endl;
    std::cout << elapsed_secs << " seconds" <<std::endl;
    free(tuples);
}