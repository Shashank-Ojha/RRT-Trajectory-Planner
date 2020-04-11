/**
 *  @file Search.h
 *  @brief Defines an API for the search methods
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

#ifndef __SEARCH_H
#define __SEARCH_H

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Graph.h"

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
    static vector<Node*> a_star(Node *start, Node *target, 
                                Graph<Node> &g, 
                                double heuristic(Node* n, Node *target));
};

/****************************************************************************/

                            /* Implementation */

/****************************************************************************/



/******      State Functions      ******/

template <typename Node> 
State<Node>::State(Node *data, Node *parent, double cost) {
  this->data = data;
  this->parent = parent;
  this->cost = cost;
  this->g = 0;
}

template <typename Node> 
State<Node>::State(Node *data, Node *parent, double cost, double g) {
  this->data = data;
  this->parent = parent;
  this->cost = cost;
  this->g = g;
}

template <typename Node> 
struct priority {
  size_t operator()(const State<Node> &A, const State<Node> &B) const {
    return A.g > B.g;  // Compare estimated g values
  }
};

/******      Search Functions      ******/

template <typename Node> 
vector<Node*> backtrace(unordered_map<Node*, Node*>& parents, Node* target) {
  vector<Node*> path;
  path.push_back(target);
  while (parents[target] != NULL) {
    target = parents[target];
    path.push_back(target);
  }

  reverse(path.begin(), path.end());
  return path;
}

template <typename Node> 
vector<Node*> Search<Node>::a_star(Node *start, Node *target,
                                   Graph<Node> &g,
                                   double heuristic(Node* n, Node* targset)) {
  priority_queue<State<Node>, vector<State<Node>>, priority<Node>> frontier;
  unordered_map<Node*, Node*> parents;
  unordered_set<Node*> visited;
  frontier.push(State<Node>(start, NULL, 0, 0));

  while (!frontier.empty()) {
    const State<Node> state = frontier.top();
    frontier.pop();

    if(visited.find(state.data) != visited.end()) { continue; }

    parents[state.data] = state.parent;
    visited.insert(state.data);

    if (state.data == target) { return backtrace(parents, target); }

    for (Node *neighbor : g.get_neighbors(state.data)) {
      if (visited.find(neighbor) == visited.end()) {
        double cost = state.cost + state.data->dist(*neighbor);
        double g = cost + heuristic(neighbor, target); /* Add Heuristic */
        State<Node> newState(neighbor, state.data, cost, g);
        frontier.push(newState);
      }
    }
  }

  cout << "Failed to find path in A*" << endl;
  assert(false);
}

#endif /* __SEARCH_H */