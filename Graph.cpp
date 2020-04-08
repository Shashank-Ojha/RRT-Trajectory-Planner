
#include <iostream>
#include <unordered_map>
#include <unordered_set>


using namespace std;

template <typename Node> 
class Graph
{
  public:
    int num_vertices;
    int num_edges;
    // TODO: Add KD-Tree to store vertices
    unordered_map<Node*, unordered_set<Node*>> edges;

    Graph(Node *root) {
      this->num_vertices = 1;
      this->num_edges = 0;
      this->edges[root] = unordered_set<Node*>();
    }

    void add_edge(Node *A, Node *B) {
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

    friend ostream& operator<<(ostream& os, const Graph& g) {
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

};