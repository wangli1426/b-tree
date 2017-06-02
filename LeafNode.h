//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_LEAFNODE_H
#define B_PLUS_TREE_LEAFNODE_H

#include "BPlusTree.h"
#include "Node.hpp"

template <typename K, typename V, int CAPACITY>
class LeafNode: public Node<K, V>{

    struct entry {
        K key;
        V val;
        entry(){};
        entry(K k, V v): key(k), val(v){};
    };

public:

    LeafNode():_size(0){};

    bool insert(K key, V val) {

        if (_size >= CAPACITY) {
            return false;
        }

        int l = 0, r = _size - 1;
        int m = 0;
        while (l <= r) {
            if (_entries[m].key <= key) {
                l = m + 1;
            } else {
                r = m;
            }
            m = (l + r) / 2;
        }

        if (_entries[m].key == key) {
            _entries[m].val = val;
            return true;
        }

        for (int i = m; i < _size; i++) {
            _entries[i + 1] = _entries[i];
        }


        _entries[m] = entry(key, val);
        _size ++;
        return true;
    }

    std::string toString() {
        std::string ret = "leaf node: ";
        for (int i = 0; i < _size; i++) {
            ret += std::to_string(_entries[i].key);
            if (i != _size - 1)
                ret += " ";
        }
        return ret;
    }


private:
    entry _entries[CAPACITY];
    int _size;

};

//template <typename K, typename V, int CAPACITY>
//std::ostream &operator<<(std::ostream &os, LeafNode<K, V, CAPACITY> const &m) {
//    for (int i = 0; i < m._size; i++) {
//        os << m._entries[i].key << std::endl;
//        if (i != m._size - 1)
//            os << " ";
//    }
//    return os;
//}

#endif //B_PLUS_TREE_LEAFNODE_H
