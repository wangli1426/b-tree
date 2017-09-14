//
// Created by robert on 14/9/17.
//

#ifndef B_TREE_INSERT_H
#define B_TREE_INSERT_H
#include "../trees/b_tree.h"
using namespace std;

template <typename K, typename V>
struct insert_context {
    BTree<K, V> *tree;
    typename vector<pair<K, V>>::const_iterator it_start;
    typename vector<pair<K, V>>::const_iterator it_end;
};

template <typename K, typename V>
void insert_building_block(BTree<K, V> *tree, typename vector<pair<K, V>>::const_iterator it_start,
            typename vector<pair<K, V>>::const_iterator it_end) {
    typename vector<pair<K, V>>::const_iterator it = it_start;
    int count = 0;
    while (it != it_end) {
        tree->insert((*it).first, (*it).second);
        ++it;
        ++count;
    }
    std::cout << count << "insertions in " << pthread_self() << std::endl;
};

template <typename K, typename V>
void* insert_worker(void* arg) {
    insert_context<K, V> *context = static_cast<insert_context<K, V>*>(arg);
    insert_building_block(context->tree, context->it_start, context->it_end);
}

template <typename K, typename V>
void insert(BTree<K, V> *tree, vector<pair<K, V>> tuples, int number_of_threads) {

    pthread_t * pids = new pthread_t[number_of_threads];
    insert_context<K, V> * context = new insert_context<K, V>[number_of_threads];

    typename vector<pair<K, V>>::const_iterator it = tuples.cbegin();
    int tuple_per_thread = tuples.size() / number_of_threads;

    for (int i = 0; i < number_of_threads; ++i) {
        context[i].tree = tree;
        context[i].it_start = tuples.cbegin() + i * tuple_per_thread;
        context[i].it_end = (i == (number_of_threads - 1)) ? tuples.cend() : tuples.cbegin() + (i + 1) * tuple_per_thread;
        pthread_create(&pids[i], NULL, insert_worker<K, V>, &context[i]);
    }

    for (int i = 0; i < number_of_threads; ++i) {
        pthread_join(pids[i], NULL);
    }
    std::cout << "joined" << std::endl;
    delete[] pids;
    delete[] context;

};
#endif //B_TREE_INSERT_H
