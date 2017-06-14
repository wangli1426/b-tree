//
// Created by robert on 6/6/17.
//

#include <gtest/gtest.h>
#include <vector>
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
    EXPECT_EQ("5 [3 [(1,1) (2,2)] [(3,3) (4,4)]] [8 10 [(5,5) (6,6) (7,7)] [(8,8) (9,9)] [(10,10) (11,11) (12,12)]]",
              tree.toString());
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

TEST(BPlusTree, Search) {
    BPlusTree<int, int, 4> tree;
    int value;
    EXPECT_EQ(false, tree.search(100, value));

    tree.insert(100, 100);

    EXPECT_EQ(false, tree.search(0, value));
    EXPECT_EQ(false, tree.search(200, value));

    tree.insert(101, 100);
    tree.insert(110, 110);
    tree.insert(150, 150);
    tree.insert(170, 170);

    EXPECT_EQ(false, tree.search(0, value));
    EXPECT_EQ(false, tree.search(105, value));
    EXPECT_EQ(false, tree.search(120, value));
    EXPECT_EQ(false, tree.search(160, value));
    EXPECT_EQ(false, tree.search(180, value));


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

TEST(BPlusTree, DeleteWithoutMergeTest) {
    BPlusTree<int, int, 4> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);
    tree.insert(5, 5);
    tree.insert(6, 6);

    tree.delete_key(4);
    tree.delete_key(3);

    EXPECT_EQ("3 [(1,1) (2,2)] [(5,5) (6,6)]", tree.toString());
}

TEST(BPlusTree, DeleteWithLeafNodeRebalancedAndMerged) {
    BPlusTree<int, int, 4> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);
    tree.insert(5, 5);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(8, 8);

    tree.delete_key(4);
    EXPECT_EQ("5 [(1,1) (2,2) (3,3)] [(5,5) (6,6) (7,7) (8,8)]", tree.toString());

    tree.delete_key(4);
    tree.delete_key(0);
    tree.delete_key(1);
    tree.delete_key(3);
    EXPECT_EQ("6 [(2,2) (5,5)] [(6,6) (7,7) (8,8)]", tree.toString());

    tree.delete_key(5);
    tree.delete_key(6);

    tree.delete_key(2);
    EXPECT_EQ("(7,7) (8,8)", tree.toString());

    tree.delete_key(7);
    tree.delete_key(8);

    EXPECT_EQ("", tree.toString());
}


TEST(BPlusTree, DeleteWithInnerNodeRebalancedAndMerged) {
    BPlusTree<int, int, 4> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);
    tree.insert(5, 5);
    tree.insert(6, 6);
    tree.insert(7, 7);
    tree.insert(8, 8);
    tree.insert(9, 9);
    tree.insert(10, 10);
    tree.insert(11, 11);
    tree.insert(12, 12);
    tree.insert(13, 13);
    tree.insert(14, 14);
    tree.insert(15, 15);
    tree.insert(16, 16);

    tree.delete_key(16);
    tree.delete_key(15);
    tree.delete_key(14);
    tree.delete_key(13);
    tree.delete_key(12);

    tree.delete_key(11);
    tree.delete_key(10);
    tree.delete_key(9);
    tree.delete_key(8);
    tree.delete_key(7);
    tree.delete_key(6);
    tree.delete_key(5);
    tree.delete_key(4);
    tree.delete_key(3);
    tree.delete_key(2);
    tree.delete_key(1);

    EXPECT_EQ("", tree.toString());
}

TEST(BPlusTree, KeysInsertedAndDeletedInRandomOrder) {
    const int number_of_tuples = 100000;
    std::vector<int> tuples;
    for (int i = 0; i < number_of_tuples; ++i) {
        tuples.push_back(i);
    }
    std::random_shuffle(tuples.begin(), tuples.end());


    BPlusTree<int, int, 4> tree;
    for (std::vector<int>::const_iterator it = tuples.cbegin(); it != tuples.cend(); ++it) {
        tree.insert(*it, *it);
    }

    std::random_shuffle(tuples.begin(), tuples.end());
    for (std::vector<int>::const_iterator it = tuples.cbegin(); it != tuples.cend(); ++it) {
        tree.delete_key(*it);
    }

    EXPECT_EQ("", tree.toString());

}

