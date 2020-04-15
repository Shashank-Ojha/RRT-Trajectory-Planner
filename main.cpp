#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <vector>
#include <ctime>

#include "utils/Graph.h"
#include "utils/KDTree.h"
#include "utils/Map.h"
#include "utils/Obstacle.h"
#include "utils/Point.h"
#include "utils/Search.h"


#include "Planner.h"
#include "Visualizer.h"

using namespace std;
string DEFAULT_MAP = "maps/map2.txt";

string parse_args(int argc, char *argv[]) {
  string filename = DEFAULT_MAP;
  if (argc > 1) {
    filename = string(argv[1]);
  }

  return filename;
}

double heuristic_fn(Point *n, Point* target) {
  return n->dist(*target);
}

void example1(int argc, char *argv[], Map &map) {
    Color black = {0, 0, 0};
    Color red = {1, 0, 0};
    Color blue = {0, 0, 1};
    Color green = {0, 1, 0};
    
    Point *start = new Point(-1, -3);
    Point *goal = new Point(9, 5);
    
    Graph<Point> graph = Planner::RRT(*start, *goal, map);
    vector<Point*> path = Search<Point>::a_star(start, goal, graph, heuristic_fn);
    
    Visualizer v;
    v.init(argc, argv);
    cout << "Start: " << *start << endl;
    cout << "Goal: " << *goal << endl;
    
     for (Obstacle obs : map.obstacles) {
         v.plot_obstacle(obs.convex_hull, black);
     }
  
    v.plot_graph(graph, green, green);
    v.plot_trajectory(path, black, black);
    v.plot_point(*start, red);
    v.plot_point(*goal, blue);
    
    v.run();
}

void nn_test(KDTree* tree, Point *p) {
	Point *nn = tree->nearest_neighbor(p);
	cout << "Testing point " << p->x << "," << p->y << endl;
	cout << "Neighbor " << nn->x << "," << nn->y << endl;
}

void kd_tree_testing_suite() {
  Point *init_pt = new Point(23, 24);
  KDTree *kd_tree = new KDTree(init_pt);
  kd_tree->insert_node(new Point(100, 101));
  kd_tree->insert_node(new Point(100, 100));
  kd_tree->insert_node(new Point(105, 90));
  kd_tree->insert_node(new Point(100, 100));
  kd_tree->insert_node(new Point(20, 24));
  kd_tree->insert_node(new Point(20, 20));
  kd_tree->insert_node(new Point(100, 102));
  kd_tree->insert_node(new Point(2.7, 3.14));
  cout << kd_tree->find_node(new Point(100, 102)) << "\n";
  cout << kd_tree->find_node(new Point(42, 42)) << "\n";

  kd_tree->print_inorder();

  nn_test(kd_tree, new Point(25, 25));
  nn_test(kd_tree, new Point(100, 100));
  nn_test(kd_tree, new Point(101, 101));
  nn_test(kd_tree, new Point(101, 100));
  nn_test(kd_tree, new Point(200, 200));
  nn_test(kd_tree, new Point(0.5, 0.5));
}

int main(int argc, char *argv[]) {
  /* Set random seed */
  srand((unsigned) time(0));

  string filename = parse_args(argc, argv);
  cout << filename << endl;

  Map map = Map(filename);
  example1(argc, argv, map);
}

