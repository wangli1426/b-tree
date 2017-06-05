//
// Created by Li Wang on 6/3/17.
//

#include <gtest/gtest.h>
#include <iostream>
#include "../src/inner_node.h"
#include "../src/leaf_node.h"

class InnerNodeTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    // virtual void TearDown() {}
};

TEST_F(InnerNodeTest, InsertWithoutSplit) {
    Node<int, int>* left_leaf = new LeafNode<int, int, 2>();
    Node<int, int>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(3, 3);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf, 3);
    inner_node.insert(2, 2);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3)]", inner_node.toString());

    inner_node.insert(4, 4);
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (4,4)]", inner_node.toString());
}


TEST_F(InnerNodeTest, InsertWithoutSplitWithSplitSupport) {
    Node<int, int>* left_leaf = new LeafNode<int, int, 2>();
    Node<int, int>* right_leaf = new LeafNode<int, int, 2>();;
    left_leaf->insert(1, 1);
    right_leaf->insert(3, 3);
    InnerNode<int, int, 4> inner_node(left_leaf, right_leaf, 3);

    Split<int, int> split;
    EXPECT_EQ(false, inner_node.insert_with_split_support(2, 2, split));
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3)]", inner_node.toString());

    EXPECT_EQ(false, inner_node.insert_with_split_support(4, 4, split));
    EXPECT_EQ("3 [(1,1) (2,2)] [(3,3) (4,4)]", inner_node.toString());


}