/**
 *  @file Planner.cpp
 *  @brief Implements the API defined in Planner.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <cfloat>
#include <vector>
#include <random>

#include "Planner.h"

#include "utils/Graph.h"
#include "utils/Map.h"
#include "utils/Point.h"
#include "utils/Search.h"
#include "utils/KDTree.h"

using namespace std;

/****************************************************************************/

                            /* Planner Utils */

/****************************************************************************/

Planner_Utils::Planner_Utils(Point *init_pt) {
  assert(init_pt != NULL);

  this->parents = unordered_map<Point*, Point*>();
  this->costs = unordered_map<Point*, double>();

  this->parents[init_pt] = NULL;
  this->costs[init_pt] = 0;
}

Point* Planner_Utils::get_parent(Point *p) {
  assert(p != NULL);
  assert(this->parents.find(p) != this->parents.end());
  return this->parents[p];
}

double Planner_Utils::get_cost(Point *p) {
  assert(p != NULL);
  assert(this->costs.find(p) != this->costs.end());
  return this->costs[p];
}

void Planner_Utils::add_point(Point *p, Point *parent, double cost) {
  assert(p != NULL);
  this->parents[p] = parent;
  this->costs[p] = cost;
}

void Planner_Utils::set_parent(Point *p, Point *parent) {
  assert(p != NULL);
  this->parents[p] = parent;
}

void Planner_Utils::set_cost(Point *p, double cost) {
  assert(p != NULL);
  this->costs[p] = cost;
}



/****************************************************************************/

                            /* Helper Functions */

/****************************************************************************/

/**
 * @brief Samples a random point inside the map.
 * 
 * @param width Map width.
 * @param height Map height.
 * @return A point inside the dimensions of the map.
 */
Point sample(float width, float height) {
  /* -width <= x < width */
  double x = (((double) rand() / (RAND_MAX)) * 2 * width) - width;
  /* -height <= y < height */
  double y = (((double) rand() / (RAND_MAX)) * 2 * height) - height;
  return Point(x, y);
}

/**
 * @brief Repeatedly samples random points inside the map until it is obstacle
 * free.
 * 
 * @param map A map object.
 * @return A point inside the dimensions of the map and free of obstacles.
 */
Point *get_rand_config(Map &map) {
  Point rand_p = sample(map.width, map.height);

  while (!map.is_freespace(rand_p)) {
    rand_p = sample(map.width, map.height);
  }
  
  return new Point(rand_p);
}

/**
 * @brief Returns a new point in the direction of the goal from start with at
 * most distance EPSILON.
 * 
 * @param map A map object.
 * @return A point inside the dimensions of the map and free of obstacles.
 */
Point* new_config(Point *start, Point *goal) {
  if(start->dist(*goal) <= EPSILON) {
    return goal;
  }

  double theta = start->angle(*goal);
  double x = start->x + EPSILON * cos(theta);
  double y = start->y + EPSILON * sin(theta);
  return new Point(x, y);
}

/**
 * @brief Tries to extend a branch from the tree to the goal by at most 
 * EPSILON
 * 
 * @param graph Graph of entire explored space.
 * @param tree Tree to extend from.
 * @param goal Goal point to extend to.
 * @param map A map object.
 * @return A point inside the dimensions of the map and free of obstacles.
 */
pair<Point*, status_t> extend(Graph<Point> &graph, KDTree *tree, Point *goal, Map &map) {
    Point *near_p = tree->nearest_neighbor(goal);
    Point *new_p = new_config(near_p, goal);
    if (map.is_valid_path(*near_p, *new_p)) {
        tree->insert_node(new_p);
        graph.add_edge(new_p, near_p);
        if (new_p == goal) { /* Equality test is on pointers */
          return {goal, REACHED};
        }
        return {new_p, ADVANCED};
    }
    delete new_p;
    return {NULL, TRAPPED};
}

/**
 * @brief Tries to extend a branch from the tree to the goal by at most 
 * EPSILON and rewires the nearby nodes
 * 
 * @param graph Graph of entire explored space.
 * @param tree Tree to extend from.
 * @param goal Goal point to extend to.
 * @param map A map object.
 * @return A point inside the dimensions of the map and free of obstacles.
 */
pair<Point*, status_t> extend_rewired(Graph<Point> &graph, KDTree *tree, Point *goal,
                                       Planner_Utils &utils, Map &map) {
    Point *near_p = tree->nearest_neighbor(goal);
    Point *new_p = new_config(near_p, goal);
    if (map.is_valid_path(*near_p, *new_p)) {
      tree->insert_node(new_p);
      double path_cost = utils.get_cost(near_p) + near_p->dist(*new_p);
      utils.add_point(new_p, near_p, path_cost);

      Point *min_p = near_p;
      unordered_set<Point*> nearest = tree->points_in_radius(new_p, SEARCH_RADIUS);

      /* Check all nearby points to see if theirs better path to new_p */
      double min_cost = DBL_MAX;
      Point *parent = NULL;
      for (Point *neighbor : nearest) {
        if (map.is_valid_path(*neighbor, *new_p)) {
          double path_cost = utils.get_cost(neighbor) + neighbor->dist(*new_p);
          if(path_cost < utils.get_cost(new_p)) {
            min_p = neighbor;
            min_cost = path_cost;
            parent = neighbor;
          }
        }
      }

      graph.add_edge(min_p, new_p);
      utils.set_parent(new_p, parent);
      utils.set_cost(new_p, min_cost);

      /* Check if all other neighbors have shorter path through new_p */
      for (Point *neighbor : nearest) {
        if(neighbor == min_p) { continue; }
        double path_cost = utils.get_cost(new_p) + new_p->dist(*neighbor);
        if (map.is_valid_path(*neighbor, *new_p) && 
            path_cost < utils.get_cost(neighbor)) {
          Point* parent = utils.get_parent(neighbor);
          graph.remove_edge(parent, neighbor);
          graph.add_edge(new_p, neighbor);
          utils.set_parent(neighbor, new_p);
          utils.set_cost(neighbor, path_cost);   
        }
      }

      if (new_p == goal) { /* Equality test is on pointers */
        return {goal, REACHED};
      }
      return {new_p, ADVANCED};
    }
    delete new_p;
    return {NULL, TRAPPED};
}

/**
 * @brief Tries to extend a branch from the tree to the goal by at most 
 * EPSILON.
 * 
 * @param graph Graph of entire explored space.
 * @param tree Tree to extend from.
 * @param goal Goal point to extend to.
 * @param map A map object.
 * @return A point inside the dimensions of the map and free of obstacles.
 */
pair<Point*, status_t> connect(Graph<Point> &graph, KDTree *tree, Point *goal, Map &map) {
    pair<Point*, status_t> p_status;
    status_t status = ADVANCED;
    while (status == ADVANCED) {
        p_status = extend(graph, tree, goal, map);
        status = p_status.second;
    }
    return p_status;
}


/**
 * @brief Supplies heuristic function based on distance between node and goal.
 * 
 * @param n Original Point.
 * @param goal Goal Point.
 * @return Euclidean distance between n and target.
 */
double heuristic(Point *n, Point *goal) {
  return n->dist(*goal);
}

/****************************************************************************/

                            /* API Implementations */

/****************************************************************************/

/**
 * @brief RRT Planner to build random tree and return path
 * 
 * @param start Starting Point.
 * @param goal Target Point.
 * @param map A map object.
 * @return Path from start to target and the underlying graph.
 */
pair<vector<Point*>, Graph<Point>> Planner::RRT(Point *start, Point *goal, Map &map) {
  KDTree *treeA = new KDTree(start);
  KDTree *treeB = new KDTree(goal);
  Graph<Point> graph(start);
  pair<Point*, status_t> p_status;
  
  for (int i = 0; i < MAX_NODES; i++) {
      Point *rand_config = get_rand_config(map);

      p_status = extend(graph, treeA, rand_config, map);
      if (p_status.second != TRAPPED) {
          p_status = connect(graph, treeB, p_status.first, map);
          if (p_status.second == REACHED) {
              delete treeA;
              delete treeB;
              vector<Point*> path = Search<Point>::a_star(start, goal, graph, heuristic);
              return {path, graph};
          }
          swap(treeA, treeB); /* built in swap function */
      } else {
        delete rand_config;
      }
  }
    
  delete treeA;
  delete treeB;
  cout << "RRT Planner Failed" << endl;
  return {vector<Point*>(), Graph<Point>(NULL)};
}

pair<vector<Point*>, Graph<Point>> Planner::RRT_star(Point *start, Point *goal, Map &map) {
  KDTree *tree = new KDTree(start);
  Graph<Point> graph(start);
  Planner_Utils utils(start);

  pair<Point*, status_t> p_status;
  
  for (int i = 0; i < MAX_NODES; i++) {
      double rand_num = ((double) rand() / (RAND_MAX));
      Point *rand_config;
      if(rand_num < 0.1) {
        rand_config = goal;
      } else {
        rand_config = get_rand_config(map); 
      }   
      p_status = extend_rewired(graph, tree, rand_config, utils, map);
      if (p_status.first == goal) {
        delete tree;
        vector<Point*> path = Search<Point>::a_star(start, goal, graph, heuristic);
        return {path, graph};
      } else if (p_status.second == TRAPPED) {
        //  delete rand_config;
      }
  }
    
  delete tree;
  cout << "RRT* Planner Failed" << endl;
  return {vector<Point*>(), Graph<Point>(NULL)};
}
