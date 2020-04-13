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
    Point *nearest_neighbor(Point *p);
    bool insert_node(Point *p);
    Node *find_node(Point *p);
    void print_inorder();
};

/*
Class for nearest_neighbor function that holds both the node that is
closest to the point we are finding a neighbor for, and the corresponding
distance with the point
*/
class NodeDist
{
  public:
    Node *node;
    int dist;

    // Constructor
    NodeDist(Node *node, int dist);
    /* In-place operator, Update node and dist if appropriate */
    bool compare_dist(NodeDist *other);
};


#endif /* __KDTREE_H */
