//
// Created by Li Wang on 6/1/17.
//

#ifndef B_PLUS_TREE_LEAFNODE_H
#define B_PLUS_TREE_LEAFNODE_H

#include "node.h"

template <typename K, typename V, int CAPACITY>
class LeafNode: public Node<K, V>{

    struct Entry {
        K key;
        V val;
        Entry(){};
        Entry(K k, V v): key(k), val(v){};
        Entry& operator=(const Entry &r) {
            this->key = r.key;
            this->val = r.val;
            return *this;
        }
    };

public:

    LeafNode():size_(0){};

    bool insert(const K &key, const V &val) {

        int insert_position;
        const bool found = search_key_position(key, insert_position);

        if (found) {
            // update the entry.
            entries_[insert_position].val = val;
            return true;
        } else {

            if (size_ >= CAPACITY) {
                return false;
            }
            // make an empty slot for new entry
            for (int i = size_ - 1; i >= insert_position; i--) {
                entries_[i + 1] = entries_[i];
            }

            // insert the new entry.
            entries_[insert_position] = Entry(key, val);
            size_ ++;
            return true;
        }
    }

    bool insert_with_split_support(const K &key, const V &val, Split<K, V> &split) {
        int insert_position;
        const bool found = search_key_position(key, insert_position);

        if (found) {
            // update the entry.
            entries_[insert_position].val = val;
            return false;
        }

        if (size_ < CAPACITY) {
            // make an empty slot for new entry
            for (int i = size_ - 1; i >= insert_position; i--) {
                entries_[i + 1] = entries_[i];
            }

            // insert the new entry.
            entries_[insert_position] = Entry(key, val);
            size_++;
            return false;
        } else {
            // split

            bool insert_to_first_half = insert_position < CAPACITY / 2;

            int entry_index_for_right_node = CAPACITY / 2;
            LeafNode<K, V, CAPACITY>* const left = this;
            LeafNode<K, V, CAPACITY>* const right = new LeafNode<K, V, CAPACITY>();

            // move entries to the right node
            for (int i = entry_index_for_right_node, j = 0; i < CAPACITY; ++i, ++j) {
                right->entries_[j] = left->entries_[i];
                --left->size_;
                ++right->size_;
            }

            // insert
            if (insert_to_first_half)
                left->insert(key, val);
            else
                right->insert(key, val);

            split.left = left;
            split.right = right;
            split.boundary_key = right->entries_[0].key;
            return true;
        }

    }

    bool point_search(const K &k, V &v) const {
        int position;
        const bool found = search_key_position(k, position);
        if (found)
            v = entries_[position].val;
        return found;
    }

    virtual bool update(const K &k, const V &v) {
        int position;
        const bool found = search_key_position(k, position);
        if (found) {
            entries_[position].val = v;
            return true;
        } else {
            return false;
        }

    }
    virtual bool delete_key(const K &k) {
        int position;
        const bool found = search_key_position(k, position);
        if (!found)
            return false;

        for (int i = position; i < size_ - 1; ++i) {
            entries_[i] = entries_[i + 1];
        }
        -- size_;
        return true;
    }

    std::string toString() {
        std::string ret;
        for (int i = 0; i < size_; i++) {
            ret += "(" + std::to_string(entries_[i].key) + "," + std::to_string(entries_[i].val) + ")";
            if (i != size_ - 1)
                ret += " ";
        }
        return ret;
    }

private:

    bool search_key_position(const K &key, int & position) const {
        int l = 0, r = size_ - 1;
        int m = 0;
        bool found = false;
        while (l <= r) {
            m = (l + r) / 2;
            if (entries_[m].key < key) {
                l = m + 1;
            } else if (entries_[m].key == key) {
                position = m;
                return true;
            } else {
                r = m - 1;
            }
        }
        position = l;
        return false;
    }

    /**
     * TODO: store the keys and the values separately, to improve data access locality.
     */
    Entry entries_[CAPACITY];
    int size_;

};


#endif //B_PLUS_TREE_LEAFNODE_H
