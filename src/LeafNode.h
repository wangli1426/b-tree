//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_LEAFNODE_H
#define B_PLUS_TREE_LEAFNODE_H

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
        bool found = false;
        while (l <= r) {
            m = (l + r) / 2;
            if (_entries[m].key < key) {
                l = m + 1;
            } else if (_entries[m].key == key) {
                found = true;
                break;
            } else {
                r = m - 1;
            }
        }

        if (found) {
            _entries[m].val = val;
            return true;
        }
        m = l;

        for (int i = _size - 1; i >= m; i--) {
            _entries[i + 1] = _entries[i];
        }


        _entries[m] = entry(key, val);
        _size ++;
        return true;
    }

    std::string toString() {
        std::string ret;
        for (int i = 0; i < _size; i++) {
            ret += "(" + std::to_string(_entries[i].key) + "," + std::to_string(_entries[i].val) + ")";
            if (i != _size - 1)
                ret += " ";
        }
        return ret;
    }

private:
    entry _entries[CAPACITY];
    int _size;

};


#endif //B_PLUS_TREE_LEAFNODE_H
