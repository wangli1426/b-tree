//
// Created by robert on 15/9/17.
//

#ifndef B_TREE_LOCK_CONTEXT_H
#define B_TREE_LOCK_CONTEXT_H

#define READ_LOCK 1
#define WRITE_LOCK 2

#include <stack>

struct LockDescriptor {
    short lock_type;
    spinlock_t &lock;
    LockDescriptor(spinlock_t &lock, short lock_type): lock(lock), lock_type(lock_type) {};
};

typedef std::stack<LockDescriptor> LockContext;


#endif //B_TREE_LOCK_CONTEXT_H
