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

#define MAX_NODES 100
#define EPSILON 1

using namespace std;

/****************************************************************************/

                            /* Helper Functions */

/****************************************************************************/

Point sample(float width, float height) {
  double x = ((double) rand() / (RAND_MAX)) * width;    /* 0 <= x < width */
  double y = ((double) rand() / (RAND_MAX)) * height;   /* 0 <= y < height */
  return Point(x, y);
}

Point* configure(Point &near_p, Point &goal) {
    double a = near_p.angle(goal);
    double x = EPSILON * cos(a);
    double y = EPSILON * sin(a);
    return new Point(x, y);
}

pair<Point, int> extend(Graph<Point> &graph, KDTree &tree, Point &goal, Map &map) {
    cout << "in extend"<< endl;
    Point *near_p = tree.nearest_neighbor(&goal);
    cout << near_p << " near_p" << endl;
    Point *new_p = configure(*near_p, goal);
    cout << new_p << " new_p" << endl;
    if (map.is_freespace(*new_p)) {
        tree.insert_node(near_p);
        graph.add_edge(near_p, &goal);
        if (new_p->dist(goal) < 1e-2) {
            return make_pair(*new_p, REACHED);
        }
        return make_pair(*new_p, ADVANCED);
    }
    return make_pair(*new_p, TRAPPED);
}

pair<Point, int> connect(Graph<Point> &graph, KDTree &tree, Point &goal, Map &map) {
    pair<Point, int> p_status;
    int status = ADVANCED;
    while (status == ADVANCED) {
        p_status = extend(graph, tree, goal, map);
        status = p_status.second;
    }
    return p_status;
}

void swap(KDTree &treeA, KDTree &treeB) {
    KDTree treeC = treeA;
    treeA = treeB;
    treeB = treeA;
}

double heuristic(Point *n, Point *target) {
  return n->dist(*target);
}

/****************************************************************************/

                            /* API Implementations */

/****************************************************************************/

//vector<Point> Planner::RRT(Point &start, Point &goal, Map &map) {
//    KDTree treeA = KDTree(&start);
//    KDTree treeB = KDTree(&goal);
//    Graph graph = Graph(&start);
//    Point rand_p;
//    pair<Point, int> p_status;
//
//    for (int i = 0; i < MAX_NODES; i++) {
//        rand_p = sample(map.width, map.height);
//        // Ensure random sample doesn't collide with obstacle
//        while (!map.is_freespace(rand_p)) {
//            rand_p = sample(map.width, map.height);
//        }
//        p_status = extend(graph, treeA, rand_p, map);
//        if (p_status.second != TRAPPED) {
//            p_status = connect(graph, treeB, p_status.first, map);
//            if (p_status.second == REACHED) {
//                return vector<Point>();
//            }
//            swap(treeA, treeB);
//        }
//    }
//  return vector<Point>();
//}

Graph<Point> Planner::RRT(Point &start, Point &goal, Map &map) {
    KDTree treeA = KDTree(&start);
    KDTree treeB = KDTree(&goal);
    Graph<Point> graph = Graph(&start);
    Point rand_p;
    pair<Point, int> p_status;
    
    for (int i = 0; i < MAX_NODES; i++) {
        rand_p = sample(map.width, map.height);
        // Ensure random sample doesn't collide with obstacle
        cout << rand_p << endl;
        while (!map.is_freespace(rand_p)) {
            rand_p = sample(map.width, map.height);
        }
        p_status = extend(graph, treeA, rand_p, map);
        cout << p_status.first << endl;
        if (p_status.second != TRAPPED) {
            p_status = connect(graph, treeB, p_status.first, map);
            if (p_status.second == REACHED) {
                return graph;
            }
            swap(treeA, treeB);
        }
    }
  return graph;
}

vector<Point> Planner::RRT_star(Point &start, Point &goal, Map &map) {
  //TODO: implement
  return vector<Point>();
}
