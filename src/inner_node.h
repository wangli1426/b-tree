//
// Created by Li Wang on 6/3/17.
//

#ifndef B_TREE_INNER_NODE_H
#define B_TREE_INNER_NODE_H
template <typename K, typename V, CAPACITY>
class InnerNode: public Node<K, V> {
public:
    InnerNode(): size_(0) {};

    bool insert(const K &key, const V &val) {

    }

    bool point_search(const K &k, V &v) const {

    }

    bool update(const K &k, const V &v) {

    }

    bool delete_key(const K &k) {

    }

    bool insert_with_split_support(const K &key, const V &val, Split<K, V>* &split) {

    }

    std::string toString() {
        return "inner node";
    }
    K key_[CAPACITY - 1];

private:
    Node* child_[CAPACITY];
    int size_;
};

#endif //B_TREE_INNER_NODE_H
