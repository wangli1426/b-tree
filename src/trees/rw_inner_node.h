//
// Created by robert on 15/9/17.
//

#ifndef B_TREE_RW_INNER_NODE_H
#define B_TREE_RW_INNER_NODE_H
#include <stack>
#include "inner_node.h"
#include "rw_node.h"
#include "lock_context.h"
using namespace std;

template<typename K, typename V, int CAPACITY>
class RWInnerNode: public InnerNode<K, V, CAPACITY>, public RWNode {
    bool lock_coupling_search(const K &k, V &v, LockContext & lock_context) {
        const int index = locate_child_index(k);
        if (index < 0) return false;
        Node<K, V> *targeNode = child_[index];
        return targeNode->search(k, v);
    }
};


#endif //B_TREE_RW_INNER_NODE_H
