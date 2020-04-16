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
Color black = {0, 0, 0};
Color red = {1, 0, 0};
Color blue = {0, 0, 1};
Color green = {0, 1, 0};

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
    
    Point *start = new Point(-1, -3);
    Point *goal = new Point(9, 5);
    
    cout << "Start: " << *start << endl;
    cout << "Goal: " << *goal << endl;
    
    auto plan = Planner::RRT(start, goal, map);
    vector<Point*> path = plan.first;
    Graph<Point> graph = plan.second; 
    
    Visualizer v;
    v.init(argc, argv);

    for (Obstacle obs : map.obstacles) {
      v.plot_obstacle(obs.convex_hull, black);
    }
  
    v.plot_graph(graph, green, green);
    v.plot_trajectory(path, black, black);
    v.plot_point(*start, red);
    v.plot_point(*goal, blue);
    
    v.run();
}

int main(int argc, char *argv[]) {
  /* Set random seed */
  srand((unsigned) time(0));

  string filename = parse_args(argc, argv);
  cout << filename << endl;

  Map map = Map(filename);
  example1(argc, argv, map);
}

