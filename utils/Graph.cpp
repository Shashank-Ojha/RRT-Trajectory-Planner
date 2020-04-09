/**
 *  @file Graph.cpp
 *  @brief Implements the class Graph defined in Graph.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "Graph.h"

using namespace std;

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
  this->edges[root] = unordered_set<Node*>();
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
  if(this->edges.find(A) == this->edges.end()) {
    this->edges[A] = unordered_set<Node*>();
    this->num_vertices += 1;
  }
  this->edges[A].insert(B);

  // Add edge from B to A
  if(this->edges.find(B) == this->edges.end()) {
    this->edges[B] = unordered_set<Node*>();
    this->num_vertices += 1;
  }
  this->edges[B].insert(A);

  this->num_edges += 1;
}

// TODO: add nearest neighbor query function


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
  for (auto adj_map : g.edges) {
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
