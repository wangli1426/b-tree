//
// Created by robert on 7/6/17.
//

#include <set>
#include <string>
#include <algorithm>
#include "../b_plus_tree.h"
#include "../utility/generator.h"

using namespace std;
void insertion_test(const string name, const int runs, const int ntuples, const int reads, double skewness) {

    double build_time = 0, search_time = 0;
    int i = runs;
    ZipfGenerator generator(ntuples, skewness);

    int *tuples = (int *) malloc(ntuples * sizeof(int));

    for (int i = 0; i < ntuples; ++i) {
        tuples[i] = i;
    }

    random_shuffle(&tuples[0], &tuples[ntuples - 1]);

    int *search_keys = new int[reads];
    for (int i = 0; i < reads; ++i) {
        search_keys[i] = generator.gen();
    }

    while (i--) {

        std::set<int> s;
        BPlusTree<int, int, 64> tree;

        int value;
        clock_t begin = clock();
//        std::sort(tuples, tuples + n_tuples);
        for (int i = 0; i < ntuples; ++i) {
            tree.insert(tuples[i], value);
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        build_time += elapsed_secs;



        begin = clock();
        for (int i = 0; i < reads; ++i) {
            tree.search(search_keys[i], value);
        }
        end = clock();
        search_time += double(end - begin) / CLOCKS_PER_SEC;
    }
    delete[] tuples;
    delete[] search_keys;

    cout << "[" << name.c_str() << "]: " << "#. of runs: " << runs << ", #. of tuples: " << ntuples <<
            ", Insert: " << ntuples * runs / build_time / 1000000 << " M tuples / s" <<
            ", Search: " << ntuples * runs / search_time / 1000000 << " M tuples / s" <<
         endl;
}