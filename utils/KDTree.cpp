/**
 *  @file KDTree.cpp
 *  @brief Implements KDTree data structure as defined in KDTree.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include "Point.h"
#include "KDTree.h"

Node::Node(Point *root) {
  this->curr = root;
  this->left = NULL;
  this->right = NULL;
}

Node::Node(Point *root, Node *left, Node *right) {
  this->curr = root;
  this->left = left;
  this->right = right;
}

KDTree::KDTree(Point *init_pt) {
  Node *root = new Node(init_pt);
}

Point *KDTree::nearest_neighbor(Point *p) {
  (void)p;
  return NULL;
}

/* Function Prototypes */
bool KDTree::insert_node(Point *p) {
  Node *root = this->root;
  return false;
}

/*
For k-NN search will need a depth parameter to find what dimension to use as
splitting criterion - formula is depth % k, where depth is how
many nodes you have searched through (0-indexed) and k is the dimension of the
points
*/
Point *KDTree::find_node(Point *p) {
  //
  return NULL;
}
