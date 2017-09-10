//
// Created by robert on 7/6/17.
//

#include <set>
#include <string>
#include <algorithm>
#include "../b_plus_tree.h"

using namespace std;
void insertion_test(const string name, const int runs, const int tuples) {

    double build_time = 0, search_time = 0;
    int i = runs;
    while (i--) {

        std::set<int> s;
        BPlusTree<int, int, 64> tree;
        const size_t n_tuples = tuples;
        int *tuples = (int *) malloc(n_tuples * sizeof(int));

        for (int i = 0; i < n_tuples; ++i) {
            tuples[i] = i;
        }

        random_shuffle(&tuples[0], &tuples[n_tuples]);


        int value;
        clock_t begin = clock();
//        std::sort(tuples, tuples + n_tuples);
        for (int i = 0; i < n_tuples; ++i) {
            tree.insert(tuples[i], value);
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        build_time += elapsed_secs;



        begin = clock();
        for (int i = 0; i < n_tuples; ++i) {
            tree.search(tuples[i], value);
        }
        end = clock();
        search_time += double(end - begin) / CLOCKS_PER_SEC;

        free(tuples);
    }

    cout << "[" << name.c_str() << "]: " << "runs: " << runs << " tuples: " << tuples <<
            " Insert: " << tuples * runs / build_time / 1000000 << " M tuples / s" <<
            " Search: " << tuples * runs / search_time / 1000000 << " M tuples / s" <<
         endl;
}