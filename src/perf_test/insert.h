//
// Created by robert on 14/9/17.
//

#ifndef B_TREE_INSERT_H
#define B_TREE_INSERT_H
using namespace std;
template <typename K, typename V>
void insert(BTree<K, V> *tree, vector<pair<K, V>> tuples, int number_of_threads) {
    for (typename vector<pair<K, V>>::const_iterator it = tuples.cbegin(); it != tuples.cend(); ++it) {
        tree->insert((*it).first, (*it).second);
    }
};
#endif //B_TREE_INSERT_H
