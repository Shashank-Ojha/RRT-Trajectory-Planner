/**
 *  @file Graph.h
 *  @brief Defines a class to create and manage a graph = (V, E)
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __GRAPH_H
#define __GRAPH_H

#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename Node> 
class Graph {
  public:
    /* Data */
    int num_vertices;
    int num_edges;
    unordered_map<Node*, unordered_set<Node*>> adj_list;

    /* Constructors */
    Graph(Node *root);

    /* Function Prototypes */
    void add_edge(Node *A, Node *B);
    unordered_set<Node*> get_neighbors(Node *n);

    /* Output Stream Definition */
    friend ostream& operator<<(ostream& os, const Graph& g);
};

#endif /* __GRAPH_H */
