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

using namespace std;

/****************************************************************************/

                            /* Helper Functions */

/****************************************************************************/

Point sample(float width, float height) {
  double x = ((double) rand() / (RAND_MAX)) * width;    /* 0 <= x < width */
  double y = ((double) rand() / (RAND_MAX)) * height;   /* 0 <= y < height */
  return Point(x, y);
}

int extend(Graph<Point> &graph, Point &goal) {
  //TODO: implement
  return REACHED;
}

int connect(Graph<Point> &graph, Point &goal) {
  //TODO: implement
  return TRAPPED;
}

double heuristic(Point *n, Point *target) {
  return n->dist(*target);
}

/****************************************************************************/

                            /* API Implementations */

/****************************************************************************/

vector<Point> Planner::RRT(Point &start, Point &goal, Map &map) {
  //TODO: implement
  return vector<Point>();
}

vector<Point> Planner::RRT_star(Point &start, Point &goal, Map &map) {
  //TODO: implement
  return vector<Point>();
}
