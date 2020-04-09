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
  (void)root;
}

Node::Node(Point *root, Node *left, Node *right) { 
  (void)root;
  (void)left;
  (void)right;
}

/* Function Prototypes */
bool Node::insert_node(Point *p) {
  (void)p;
  return false;
}

Point *Node::find_node(Point *p) {
  (void)p;
  return NULL;
}


KDTree::KDTree(Point *root) {
  (void)root;
}

Point *KDTree::nearest_neighbor(Point *p) {
  (void)p;
  return NULL;
}


