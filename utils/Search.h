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

                          /* Node Implementation */

/****************************************************************************/


/**
 * @brief Constructor for a state
 * 
 * @param data Pointer to data.
 * @param parent Pointer to parent.
 * @param cost True cost to node.
 * @param g Estimated cost to goal going through this node.
 * @return New output stream with graph inside stream.
 */
template <typename Node> 
State<Node>::State(Node *data, Node *parent, double cost, double g) {
  this->data = data;
  this->parent = parent;
  this->cost = cost;
  this->g = g;
}

/**
 * @brief Priority function to determine which order to visit states.
 * 
 * Note: PQ pick element from the right (which should be the smallest 
 *  given our ordering).
 * 
 * @param A State 1.
 * @param A State 2.
 * @return True if B has priority over A (minheap).
 */
template <typename Node> 
struct priority {
  size_t operator()(const State<Node> &A, const State<Node> &B) const {
    return A.g > B.g;  // Compare estimated g values
  }
};

/****************************************************************************/

                            /* Search Functions */

/****************************************************************************/

/**
 * @brief Backtraces up the parents to find full path to target.
 * 
 * @param parents Map of parent pointers.
 * @param target Final state in path.
 * @return Full path of states from start to target.
 */
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

/**
 * @brief Computes A* search with the given heuristic from start to target
 * using the provided Graph.
 * 
 * @param start Initial state in path.
 * @param target Final state in path.
 * @param g Graph to search in.
 * @param heuristic heuristic function to aid search.
 * @return Full path of states from start to target or error if not found.
 */
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
  return vector<Node*>();
}

#endif /* __SEARCH_H */