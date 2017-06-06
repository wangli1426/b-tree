//
// Created by robert on 6/6/17.
//

#include <gtest/gtest.h>
#include <iostream>
#include <set>
#include "../src/b_plus_tree.h"


TEST(BPlusTreeTest, InsertionTest) {
    BPlusTree<int, int, 4> tree;
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(6, 6);

    EXPECT_EQ("(1,1) (2,2) (3,3) (6,6)", tree.toString());

    tree.insert(10, 10);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (6,6) (10,10)]", tree.toString());

    tree.insert(9, 9);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (6,6) (9,9) (10,10)]", tree.toString());

    tree.insert(8, 8);
    EXPECT_EQ("3 8 [(1,1) (2,2)] [(3,3) (6,6)] [(8,8) (9,9) (10,10)]", tree.toString());

    tree.insert(7, 7);
    tree.insert(4, 4);
    tree.insert(5, 5);
    EXPECT_EQ("3 5 8 [(1,1) (2,2)] [(3,3) (4,4)] [(5,5) (6,6) (7,7)] [(8,8) (9,9) (10,10)]", tree.toString());

    tree.insert(11, 11);
    tree.insert(12, 12);
    EXPECT_EQ("5 [3 [(1,1) (2,2)] [(3,3) (4,4)]] [8 10 [(5,5) (6,6) (7,7)] [(8,8) (9,9)] [(10,10) (11,11) (12,12)]]", tree.toString());
}

TEST(BPlusTreeTest, InsertAndQueryTest) {
    BPlusTree<int, int, 5> tree;
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.insert(6, 6);
    tree.insert(2, 2);
    tree.insert(7, 7);
    tree.insert(10, 10);
    tree.insert(9, 9);
    tree.insert(8, 8);
    tree.insert(11, 11);
    tree.insert(4, 4);
    tree.insert(5, 5);
    tree.insert(12, 12);

    for (int i = 1; i <= 12; ++i) {
        int value;
        EXPECT_EQ(true, tree.search(i, value));
        EXPECT_EQ(i, value);
    }
}

TEST(BPlusTreeTest, InsertReverseOrderAndQueryTest) {
    BPlusTree<int, int, 2> tree;
    tree.insert(11, 11);
    tree.insert(12, 12);
    tree.insert(10, 10);
    tree.insert(9, 9);
    tree.insert(8, 8);
    tree.insert(7, 7);
    tree.insert(5, 5);
    tree.insert(4, 4);
    tree.insert(6, 6);
    tree.insert(3, 3);
    tree.insert(2, 2);
    tree.insert(1, 1);

    for (int i = 1; i <= 12; ++i) {
        int value;
        EXPECT_EQ(true, tree.search(i, value));
        EXPECT_EQ(i, value);
    }
}

TEST(BPlusTree, MassiveRandomInsertionAndQuery) {
    std::set<int> s;
    BPlusTree<int, int, 4> tree;
    const int tuples = 100000;
    const int range = tuples * 10;

    for (int i = 0; i < tuples; ++i) {
        const int r = std::rand() % range;
        s.insert(r);
        tree.insert(r, r);
    }

//    for (int i = 0; i < tuples; ++i) {
//        const int r = std::rand() % range;
//        size_t size = s.size();
//        s.insert(r);
//        if (size != s.size()) {
//            if (r < 6) {
//                std::cout << "small value " << std::endl;
//            }
//            tree.insert(r, r);
//            int value = -1;
//            bool result = tree.search(r, value);
//            if (!result) {
//                std::cout << "to insert " << r << std::endl;
//                break;
//            }
//            EXPECT_EQ(r, value);
//            std::cout << i <<": " << r << std::endl;
//            std::cout << tree.toString() << std::endl;
//        }
//
//    }

//    for (std::set<int>::const_iterator iterator = s.cbegin(); iterator != s.cend(); ++iterator) {
//        tree.insert(*iterator, *iterator);
//        int value;
//        tree.search(*iterator, value);
//        EXPECT_EQ(*iterator, value);
//        std::cout << *iterator << " is inserted." << std::endl;
//    }

    for (int i = 0; i < range; ++i) {
        int value = -1;
        if (s.find(i) != s.cend()) {
            EXPECT_EQ(true, tree.search(i, value));
            EXPECT_EQ(i, value);
        } else {
            EXPECT_EQ(false, tree.search(i, value));
        }
    }
}

