//
// Created by robert on 15/9/17.
//

#ifndef B_TREE_THREAD_SAFE_B_PLUS_TREE_H
#define B_TREE_THREAD_SAFE_B_PLUS_TREE_H

#include "vanilla_b_plus_tree.h"
#include "../utility/read_write_spin_lock.h"
template <typename K, typename V, int CAPACITY>
class ThreadSafeBPlusTree: protected VanillaBPlusTree<K, V, CAPACITY>, public BTree<K, V> {
public:
    ThreadSafeBPlusTree():VanillaBPlusTree<K, V, CAPACITY>() {

    }

    void insert(const K &k, const V &v) {

    }
    bool delete_key(const K &k) {

    }
    virtual bool search(const K &k, V &v) {

    }
    virtual void clear() {

    }
    class Iterator : public BTree<K, V>::Iterator {
    public:
        virtual bool next(K & key, V & val) {
            return false;
        };
    };
    virtual Iterator* range_search(const K & key_low, const K & key_high) {

    };

};

#endif //B_TREE_THREAD_SAFE_B_PLUS_TREE_H
