//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_LEAFNODE_H
#define B_PLUS_TREE_LEAFNODE_H

#include "node.h"

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

    bool insert(const K &key, const V &val) {

        if (_size >= CAPACITY) {
            return false;
        }

        int insert_position;
        const bool found = search_key_position(key, insert_position);

        if (found) {
            // update the entry.
            _entries[insert_position].val = val;
            return true;
        } else {

            // make an empty slot for new entry
            for (int i = _size - 1; i >= insert_position; i--) {
                _entries[i + 1] = _entries[i];
            }

            // insert the new entry.
            _entries[insert_position] = entry(key, val);
            _size++;
            return true;
        }
    }

    bool point_search(const K &k, V &v) const {
        int position;
        const bool found = search_key_position(k, position);
        if (found)
            v = _entries[position].val;
        return found;
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

    bool search_key_position(const K &key, int & position) const {
        int l = 0, r = _size - 1;
        int m = 0;
        bool found = false;
        while (l <= r) {
            m = (l + r) / 2;
            if (_entries[m].key < key) {
                l = m + 1;
            } else if (_entries[m].key == key) {
                position = m;
                return true;
            } else {
                r = m - 1;
            }
        }
        position = l;
        return false;
    }

    entry _entries[CAPACITY];
    int _size;

};


#endif //B_PLUS_TREE_LEAFNODE_H
