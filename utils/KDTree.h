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

class Node
{
  public:
    /* Data */
    Point *curr;
    Node *left;
    Node *right;

    /* Constructors */
    Node(Point *root);
    Node(Point *root, Node *left, Node *right);
};

class KDTree
{
  public:
    /* Data */
    Node *root;

    /* Constructors */
    KDTree(Point *init_pt);

    /* Function Prototypes */
    Point *nearest_neighbor(Point *p);
    bool insert_node(Point *p);
    Point *find_node(Point *p);
};

#endif /* __KDTREE_H */
