//
// Created by robert on 14/9/17.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H
template <typename K, typename V>
class BTree {
public:
    virtual void insert(const K &k, const V &v) = 0;
    virtual bool delete_key(const K &k) = 0;
    virtual bool search(const K &k, V &v) const = 0;
    virtual void clear() = 0;
};
#endif //B_TREE_B_TREE_H
