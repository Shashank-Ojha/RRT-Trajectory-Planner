/**
 *  @file Planner.cpp
 *  @brief Implements the API defined in Planner.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <vector>
#include <random>

#include "Planner.h"

#include "utils/Graph.h"
#include "utils/Map.h"
#include "utils/Point.h"
#include "utils/Search.h"
#include "utils/KDTree.h"

#define MAX_NODES 200
#define EPSILON 0.5

using namespace std;

/****************************************************************************/

                            /* Helper Functions */

/****************************************************************************/

Point sample(float width, float height) {
  double x = (((double) rand() / (RAND_MAX)) * 2 * width) - width;    /* -width <= x < width */
  double y = (((double) rand() / (RAND_MAX)) * 2 * height) - height;   /* -height <= y < height */
  return Point(x, y);
}

Point *get_rand_config(Map &map) {
  Point rand_p = sample(map.width, map.height);

  while (!map.is_freespace(rand_p)) {
    rand_p = sample(map.width, map.height);
  }
  
  return new Point(rand_p);
}

Point* extension(Point *near_p, Point *goal) {
    double theta = near_p->angle(*goal);
    double x = near_p->x + EPSILON * cos(theta);
    double y = near_p->y + EPSILON * sin(theta);
    return new Point(x, y);
}

pair<Point*, status_t> extend(Graph<Point> &graph, KDTree &tree, Point *goal, Map &map) {
    Point *near_p = tree.nearest_neighbor(goal);
    Point *new_p = extension(near_p, goal);
    if (map.is_freespace(*new_p)) {
        if (new_p->dist(*goal) < EPSILON) {
          tree.insert_node(goal);
          graph.add_edge(goal, near_p);
          delete new_p;
          return make_pair(goal, REACHED);
        } else {
            tree.insert_node(new_p);
            graph.add_edge(new_p, near_p);
            return make_pair(new_p, ADVANCED);
        }
    }
    return make_pair(new_p, TRAPPED);
}

pair<Point*, status_t> connect(Graph<Point> &graph, KDTree &tree, Point *goal, Map &map) {
    pair<Point*, status_t> p_status;
    status_t status = ADVANCED;
    while (status == ADVANCED) {
        p_status = extend(graph, tree, goal, map);
        status = p_status.second;
    }
    return p_status;
}

void swap(KDTree &treeA, KDTree &treeB) {
    KDTree treeC = treeA;
    treeA = treeB;
    treeB = treeC;
}

double heuristic(Point *n, Point *target) {
  return n->dist(*target);
}

/****************************************************************************/

                            /* API Implementations */

/****************************************************************************/

//vector<Point> Planner::RRT(Point &start, Point &goal, Map &map)
Graph<Point> Planner::RRT(Point &start, Point &goal, Map &map) {
    KDTree treeA = KDTree(&start);
    KDTree treeB = KDTree(&goal);
    Graph<Point> graph = Graph(&start);
    pair<Point*, int> p_status;
    
    for (int i = 0; i < MAX_NODES; i++) {
        Point *rand_config = get_rand_config(map);

        p_status = extend(graph, treeA, rand_config, map);
        if (p_status.second != TRAPPED) {
            p_status = connect(graph, treeB, p_status.first, map);
            if (p_status.second == REACHED) {
                return graph;
            }
            swap(treeA, treeB);
        } else {
          delete rand_config;
        }
    }
  return graph;
}

vector<Point> Planner::RRT_star(Point &start, Point &goal, Map &map) {
  //TODO: implement
  return vector<Point>();
}
