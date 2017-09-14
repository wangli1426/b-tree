//
// Created by robert on 7/6/17.
//

#include <set>
#include <string>
#include <algorithm>
#include "../trees/vanilla_b_plus_tree.h"
#include "../utility/generator.h"
#include "insert.h"

using namespace std;
template <typename K, typename V>
void benchmark(BTree<K, V> *tree, const string name, const int runs, const int ntuples, const int reads,
               double skewness) {

    double build_time = 0, search_time = 0;
    int run = runs;
    int found = 0;
    ZipfGenerator generator(ntuples, skewness);

//    int *tuples = new int[ntuples];

    vector<pair<K, V>> tuples;

    for (int i = 0; i < ntuples; ++i) {
        tuples.push_back(make_pair(i, i));
    }

    random_shuffle(tuples.begin(), tuples.end());

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
        insert<K, V>(tree, tuples, 1);
        clock_t end = clock();

        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        build_time += elapsed_secs;



        begin = clock();

        for (int i = 0; i < reads; ++i) {
            found += tree->search(search_keys[i], value);
        }
        end = clock();
        search_time += double(end - begin) / CLOCKS_PER_SEC;
    }
    delete[] search_keys;

    cout << "[" << name.c_str() << "]: " << "#. of runs: " << runs << ", #. of tuples: " << ntuples << " reads: "
         << reads * runs <<" found: " << found << ", Insert: " << ntuples * runs / build_time / 1000000
         << " M tuples / s" << ", Search: " << reads * runs / search_time / 1000000 << " M tuples / s" <<
         endl;
}