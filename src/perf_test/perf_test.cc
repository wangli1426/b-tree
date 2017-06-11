//
// Created by robert on 7/6/17.
//

#include <set>
#include "../b_plus_tree.h"

double insertion_test() {

    int runs = 10;
    double time = 0;
    int i = runs;
    while (i--) {

        std::set<int> s;
        BPlusTree<int, int, 8> tree;
        const size_t n_tuples = 1000000;
        const size_t range = n_tuples * 10;
        int *tuples = (int *) malloc(n_tuples * sizeof(int));

        for (size_t i = 0; i < n_tuples; ++i) {
            tuples[i] = (int) (std::rand() % range);
        }

        clock_t begin = clock();

        for (int i = 0; i < n_tuples; ++i) {
            tree.insert(tuples[i], tuples[i]);
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        time += elapsed_secs;

        free(tuples);
    }

    return time / runs;
}