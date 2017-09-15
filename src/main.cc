#include <iostream>
#include <set>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <map>
#include "trees/vanilla_b_plus_tree.h"
#include "trees/inner_node.h"
#include "perf_test/perf_test.cc"
#include "utility/generator.h"
#include "trees/thread_safe_b_plus_tree.h"


class Entry {
public:
    virtual int get() {
        return 1;
    }
};

class Entry2: public Entry {
public:
    int get() {
        return 2;
    }
};

class A {
public:

    int get() {
        return a->get();
    }

    void doit() {
        create();
    }

protected:
    virtual void create() {
        a = new Entry();
    }

    Entry* a;
};

class B: public A {
protected:
    void create() {
        a = new Entry2();
    }
};

int main() {
//    VanillaBPlusTree<int, int, 64> bTree = VanillaBPlusTree<int, int, 64>();
//    benchmark<int, int>(&bTree, "test1", 2, 1000000, 1000000, 1000000, 1);
//    ThreadSafeBPlusTree<int, int, 64> tree;

    A *a = new A();
    A *b = new B();
    a->doit();
    b->doit();

    std::cout << "a.get: " << a->get() << std::endl;
    std::cout << "b.get: " << b->get() << std::endl;

    delete a;
    delete b;



}