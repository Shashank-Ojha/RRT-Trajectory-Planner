#ifndef __GRAPH_H
#define __GRAPH_H

#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename Node> 
class Graph
{
  public:
    int num_vertices;
    int num_edges;

    unordered_map<Node*, unordered_set<Node*>> edges;

    Graph(Node *root);

    void add_edge(Node *A, Node *B);

    friend ostream& operator<<(ostream& os, const Graph& g);
};

#endif /* __GRAPH_H */
