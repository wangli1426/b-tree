//
// Created by robert on 15/9/17.
//

#ifndef B_TREE_RW_LEAF_NODE_H
#define B_TREE_RW_LEAF_NODE_H
#include "leaf_node.h"
#include "rw_node.h"

template<typename K, typename V, CAPACITY>
class RWLeafNode: public LeafNode<K, V, CAPACITY>, public RWNode {

};


#endif //B_TREE_RW_LEAF_NODE_H
