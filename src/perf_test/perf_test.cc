//
// Created by robert on 7/6/17.
//

#include <set>
#include <string>
#include <algorithm>
#include "../trees/vanilla_b_plus_tree.h"
#include "../utility/generator.h"

using namespace std;
template <typename K, typename V>
void insertion_test(BTree<K, V> *tree, const string name, const int runs, const int ntuples, const int reads, double skewness) {

    double build_time = 0, search_time = 0;
    int run = runs;
    int found = 0;
    ZipfGenerator generator(ntuples, skewness);

    int *tuples = new int[ntuples];

    for (int i = 0; i < ntuples; ++i) {
        tuples[i] = i;
    }

    random_shuffle(&tuples[0], &tuples[ntuples - 1]);

    int *search_keys = new int[reads];
    for (int i = 0; i < reads; ++i) {
        search_keys[i] = generator.gen();
    }

    while (run--) {
        tree->clear();
        std::set<int> s;
//        VanillaBPlusTree<int, int, 128> tree;

        int value;
        clock_t begin = clock();
//        std::sort(tuples, tuples + n_tuples);
        for (int i = 0; i < ntuples; ++i) {
            tree->insert(tuples[i], tuples[i]);
        }

        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        build_time += elapsed_secs;



        begin = clock();

        for (int i = 0; i < reads; ++i) {
            found += tree->search(search_keys[i], value);
//            if (found && rand() % 10000 == 0) {
//                std::cout << "key: " << search_keys[i] << " val: " << value << std::endl;
//            }
        }
        end = clock();
        search_time += double(end - begin) / CLOCKS_PER_SEC;
    }
    delete[] tuples;
    delete[] search_keys;

    cout << "[" << name.c_str() << "]: " << "#. of runs: " << runs << ", #. of tuples: " << ntuples << " reads: "
         << reads * runs <<" found: " << found << ", Insert: " << ntuples * runs / build_time / 1000000
         << " M tuples / s" << ", Search: " << reads * runs / search_time / 1000000 << " M tuples / s" <<
         endl;
}