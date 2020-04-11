#include <iostream>
#include <vector>

#include "utils/Graph.h"
#include "utils/KDTree.h"
#include "utils/Map.h"
#include "utils/Obstacle.h"
#include "utils/Point.h"
#include "utils/Search.h"

#include "Planner.h"
#include "Visualizer.h"

using namespace std;
string DEFAULT_MAP = "maps/map1.txt"; 

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

int main(int argc, char *argv[]) {

  // Color black = {0, 0, 0};

  string filename = parse_args(argc, argv);
  cout << filename << endl;

  Point *init = new Point();
  Point *one = new Point(1, 0);
  Point *two = new Point(2, 0);
  Point *three = new Point(3, 0);
  Point *med = new Point(1, 1);

  Graph<Point> g(init);
  g.add_edge(init, one);
  g.add_edge(one, two);
  g.add_edge(two, three);
  g.add_edge(init, med);
  g.add_edge(med, three);

  vector<Point*> path = Search<Point>::a_star(init, three, g, heuristic_fn);

  for (Point *p : path) {
    cout << *p << endl;
  }

  Map map = Map(filename);
  
  // Visualizer v;
  // v.init(argc, argv);
  // v.plot_obstacle(polygon, black);
  // v.run();
}
