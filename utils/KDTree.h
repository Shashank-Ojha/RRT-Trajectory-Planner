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
    Point *data;
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
    /*
    Args:
    Point *p: (x,y) point that we are looking for in the tree
    two bool * so the function can set values

    Returns:
    Node* the last node visited while searching for p
    bool *exists: 1 if found p is in the kdtree, 0 otherwise
    bool *go_left: if !exists, go_left gives which direction from the leaf node
    p would be placed
    */
    Node *find_node(Point *p, bool *exists, bool *go_left);
    void print_inorder(); 
};



#endif /* __KDTREE_H */
