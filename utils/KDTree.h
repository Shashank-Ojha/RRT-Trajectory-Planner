/**
 *  @file KDTree.h
 *  @brief Defines a KDTree data structure to manage 2D points. It uses
 *  a Node class internally to help it manage it its structure.
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __KDTREE_H
#define __KDTREE_H

#include "Point.h"

/* Constants for direction of node placement */
#define LEFT -1
#define RIGHT 1
#define EXISTS 0

#define K 2

class Node
{
  public:
    /* Data */
    Point *data;
    Node *left;
    Node *right;

    /* Constructors */
    Node(Point *root);
    Node(Point *root, Node *left, Node *right);
    double node_dist(Node *other);
};

class KDTree {
  public:
    /* Data */
    Node *root;

    /* Constructors */
    KDTree(Point *init_pt);

    /* Function Prototypes */
    bool insert_node(Point *p);
    Node *find_node(Point *p);
    Point *nearest_neighbor(Point *p);
    void print_inorder();
};


#endif /* __KDTREE_H */
