//
// Created by Li Wang on 6/3/17.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../src/inner_node.h"
#include "../src/leaf_node.h"


TEST(InnerNodeTest, InsertWithoutSplit) {
    LeafNode<int, int, 2>* left_leaf = new LeafNode<int, int, 2>();
    LeafNode<int, int, 2>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(3, 3);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf);
    inner_node.insert(2, 2);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3)]", inner_node.toString());

    inner_node.insert(4, 4);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (4,4)]", inner_node.toString());
}


TEST(InnerNodeTest, InsertWithoutSplitWithSplitSupport) {
    LeafNode<int, int, 2>* left_leaf = new LeafNode<int, int, 2>();
    LeafNode<int, int, 2>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(3, 3);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf);

    Split<int, int> split;
    EXPECT_EQ(false, inner_node.insert_with_split_support(2, 2, split));
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(4, 4, split));
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (4,4)]", inner_node.toString());
}

TEST(InnerNodeTest, InsertWithSplitWithSplitSupport) {
    LeafNode<int, int, 2>* left_leaf = new LeafNode<int, int, 2>();
    LeafNode<int, int, 2>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(6, 6);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf);

    Split<int, int> split;
    EXPECT_EQ(false, inner_node.insert_with_split_support(4, 4, split));
    EXPECT_EQ("6 [(1,1) (4,4)] [(6,6)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(8, 8, split));
    EXPECT_EQ("6 [(1,1) (4,4)] [(6,6) (8,8)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(10, 10, split));
    EXPECT_EQ("6 8 [(1,1) (4,4)] [(6,6)] [(8,8) (10,10)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(3, 3, split));
    EXPECT_EQ("3 6 8 [(1,1)] [(3,3) (4,4)] [(6,6)] [(8,8) (10,10)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(7, 7, split));
    EXPECT_EQ("3 6 8 [(1,1)] [(3,3) (4,4)] [(6,6) (7,7)] [(8,8) (10,10)]", inner_node.toString());

}

TEST(InnerNodeTest, InnerNodeSplit1) {
    LeafNode<int, int, 2>* left_leaf = new LeafNode<int, int, 2>();
    LeafNode<int, int, 2>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    left_leaf->insert(3, 3);
    right_leaf->insert(6, 6);
    right_leaf->insert(8, 8);
    InnerNode<int, int, 2> inner_node(left_leaf, right_leaf);

    Split<int, int> split;

    EXPECT_EQ(true, inner_node.insert_with_split_support(2, 2, split));
    EXPECT_EQ("2 [(1,1)] [(2,2) (3,3)]", split.left->toString());
    EXPECT_EQ(" [(6,6) (8,8)]", split.right->toString());
    delete split.right;
}

TEST(InnerNodeTest, InnerNodeSplit2) {
    LeafNode<int, int, 2>* left_leaf = new LeafNode<int, int, 2>();
    LeafNode<int, int, 2>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    left_leaf->insert(3, 3);
    right_leaf->insert(6, 6);
    right_leaf->insert(8, 8);
    InnerNode<int, int, 2> inner_node(left_leaf, right_leaf);

    Split<int, int> split;

    EXPECT_EQ(true, inner_node.insert_with_split_support(9, 9, split));
    EXPECT_EQ(" [(1,1) (3,3)]", split.left->toString());
    EXPECT_EQ("8 [(6,6)] [(8,8) (9,9)]", split.right->toString());
    delete split.right;
}