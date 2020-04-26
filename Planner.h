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
#include <unordered_map>

#include "utils/Graph.h"
#include "utils/Map.h"
#include "utils/Point.h"

typedef int status_t;

/* Constants to describe results of extending the tree */
#define REACHED 1
#define ADVANCED 0
#define TRAPPED -1

#define MAX_NODES 4000
#define EPSILON 0.2

#define GOAL_BIAS 0.1 
#define SEARCH_RADIUS 2 /* This should be much bigger than EPSILON */

using namespace std;

/* Used in RRT* to keep track of parents and costs of a node */
class Planner_Utils {
  public:
    /* Data */
    unordered_map<Point*, Point*> parents;
    unordered_map<Point*, double> costs;

    /* Constructors */
    Planner_Utils(Point *init_pt);

    /* Function Prototypes */
    Point* get_parent(Point *p);
    double get_cost(Point *p);

    void add_point(Point *p, Point *parent, double cost);
    void set_parent(Point *p, Point *parent);
    void set_cost(Point *p, double cost);
};


class Planner {
  
  public:
    /* Function Prototypes */
    static pair<vector<Point*>, Graph<Point>> RRT_connect(Point *start, Point *goal, Map &map);
    static pair<vector<Point*>, Graph<Point>> RRT_star(Point *start, Point *goal, Map &map);
};

#endif /* __PLANNER_H */
