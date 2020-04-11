/**
 *  @file Graph.h
 *  @brief Defines a class to create and manage a graph = (V, E)
 * 
 *  NOTE: The implementation is also found in this file instead of a separate
 *  cpp file. This is necessary for templates. For more information see:
 *    https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __GRAPH_H
#define __GRAPH_H

#include <iostream>
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

/****************************************************************************/

                            /* Implementation */

/****************************************************************************/


/**
 * @brief Graph constructor with one node. Node can have any type.
 *
 * @param root Pointer to a vertex object.
 * @return Graph containing just the root as a vertex.
 */
template <typename Node> 
Graph<Node>::Graph(Node *root) {
  this->num_vertices = 1;
  this->num_edges = 0;
  this->adj_list[root] = unordered_set<Node*>();
}

/**
 * @brief Adds an edge in the graph between Nodes A and B. Graph adds A and/or
 * B as vertices if they are not already present. Note that this function 
 * allows you to create disconnected graphs.
 *
 * @param A Pointer to an first vertex object.
 * @param B Pointer to an second vertex object.
 * @return Void.
 */
template <typename Node> 
void Graph<Node>::add_edge(Node *A, Node *B) {
  // Add edge from A to B
  if(this->adj_list.find(A) == this->adj_list.end()) {
    this->adj_list[A] = unordered_set<Node*>();
    this->num_vertices += 1;
  }
  this->adj_list[A].insert(B);

  // Add edge from B to A
  if(this->adj_list.find(B) == this->adj_list.end()) {
    this->adj_list[B] = unordered_set<Node*>();
    this->num_vertices += 1;
  }
  this->adj_list[B].insert(A);

  this->num_edges += 1;
}

/**
 * @brief Returns the neighbors of the given node.
 *
 * @param n Pointer to a Node.
 * @return Neighbors of that node.
 */
template <typename Node> 
unordered_set<Node*> Graph<Node>::get_neighbors(Node *n) {
  return this->adj_list[n];
}


/**
 * @brief Adds support for printing Graphs.
 * 
 * @param os Output stream.
 * @param g Graph Object.
 * @return New output stream with graph inside stream.
 */
template <typename Node> 
ostream& operator<<(ostream& os, const Graph<Node>& g) {
  os << "Number of vertices: " << g.num_vertices << endl;
  os << "Number of edges: " << g.num_edges << endl;
  for (auto adj_map : g.adj_list) {
      Node *key = adj_map.first;
      os << *key << " --> [";
      bool first = true;
      for (auto value : adj_map.second) {
        if (!first) {
          os << ", ";
        }
        first = false;
        os << *value;
      }
      os << "]" << endl;
  }
  return os;
}

#endif /* __GRAPH_H */
