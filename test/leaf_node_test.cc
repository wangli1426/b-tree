//
// Created by Li Wang on 6/2/17.
//
#include <gtest/gtest.h>
#include <iostream>
#include "../src/LeafNode.h"

TEST(LeafNode, InsertionWithOverflow) {

    LeafNode<int, int, 5> leafNode;
    leafNode.insert(1, 1);
    leafNode.insert(3, 2);
    leafNode.insert(2, 5);
    leafNode.insert(-1, 5);
    leafNode.insert(6, 2);
    EXPECT_EQ("(-1,5) (1,1) (2,5) (3,2) (6,2)", leafNode.toString());
}

TEST(LeafNode, InsertionWithOverflowDouble) {

    LeafNode<double, int, 5> leafNode;
    leafNode.insert(1.3, 1);
    leafNode.insert(3.2, 2);
    leafNode.insert(2.5, 5);
    leafNode.insert(-1.0, 5);
    leafNode.insert(-6.4, 2);
    EXPECT_EQ("(-6.400000,2) (-1.000000,5) (1.300000,1) (2.500000,5) (3.200000,2)", leafNode.toString());
}

TEST(LeafNode, InsertionAndUpdate) {
    LeafNode<int, int, 5> leaf_node;
    leaf_node.insert(1, 2);
    leaf_node.insert(1, 3);
    EXPECT_EQ("(1,3)", leaf_node.toString());
}

TEST(LeafNode, Search) {
    LeafNode<int, int, 10> leaf_node;
    leaf_node.insert(1, 5);
    leaf_node.insert(5, 8);
    leaf_node.insert(-1, 222);
    int result;
    EXPECT_EQ(true, leaf_node.point_search(1, result));
    EXPECT_EQ(5, result);

    EXPECT_EQ(true, leaf_node.point_search(5, result));
    EXPECT_EQ(8, result);

    EXPECT_EQ(true, leaf_node.point_search(-1, result));
    EXPECT_EQ(222, result);
}