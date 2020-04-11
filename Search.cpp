/**
 *  @file Search.cpp
 *  @brief Implementation of API defined in Search.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __SEARCH_CPP
#define __SEARCH_CPP

#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/Point.h"
#include "utils/Graph-impl.cpp"

#include "Search.h"

using namespace std;

/****************************************************************************/

                            /* State Functions */

/****************************************************************************/

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

/****************************************************************************/

                            /* Search Functions */

/****************************************************************************/

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
vector<Node*> Search<Node>::a_star(Node *start, Node *target, Graph<Node> &g) {
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
        double g = cost + neighbor->dist(*target); /* Add Heuristic */
        State<Node> newState(neighbor, state.data, cost, g);
        frontier.push(newState);
      }
    }
  }

  cout << "Failed to find path in A*" << endl;
  assert(false);
}

#endif /* __SEARCH_CPP */
