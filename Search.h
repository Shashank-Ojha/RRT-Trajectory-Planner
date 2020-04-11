/**
 *  @file Search.h
 *  @brief Defines an API for the search methods
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __SEARCH_H
#define __SEARCH_H

#include <vector>

#include "utils/Graph.h"

/* Class to keep track of information related to visited states */
template <typename Node> 
class State {
  public:
    /* Data */
    Node *data;
    Node *parent;
    double cost;
    double g;

    /* Constructors */
    State(Node *data, Node *parent, double cost);
    State(Node *data, Node *parent, double cost, double g);
};

template <typename Node> 
class Search {
  public:
    /* Function Prototypes */
    static vector<Node*> a_star(Node *start, Node *target, Graph<Node> &g);
};

#endif /* __SEARCH_H */