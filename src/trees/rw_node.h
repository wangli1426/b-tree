//
// Created by robert on 15/9/17.
//

#ifndef B_TREE_RW_NODE_H
#define B_TREE_RW_NODE_H

#include "../utility/read_write_spin_lock.h"

class RWNode {
public:
    spinlock_t& get_lock() {
        return &lock_;
    }
private:
    spinlock_t lock_;
};
#endif //B_TREE_RW_NODE_H
