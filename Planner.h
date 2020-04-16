/**
 *  @file Planner.h
 *  @brief Defines an API for the RRT planning methods
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#ifndef __PLANNER_H
#define __PLANNER_H

#include <vector>

#include "utils/Graph.h"
#include "utils/Map.h"
#include "utils/Point.h"

typedef int status_t;

/* Constants to describe results of extending the tree */
#define REACHED 1
#define ADVANCED 0
#define TRAPPED -1

using namespace std;

class Planner {
  
  public:
    /* Function Prototypes */
    static pair<vector<Point*>, Graph<Point>> RRT(Point *start, Point *goal, Map &map);
    static pair<vector<Point*>, Graph<Point>> RRT_star(Point *start, Point *goal, Map &map);
};

#endif /* __PLANNER_H */
