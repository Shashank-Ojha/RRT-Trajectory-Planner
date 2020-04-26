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

#define MS 1000

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

double mean(vector<double> data) {
    double sum = 0;
    for (double d : data) {
        sum += d;
    }
    return (sum / data.size());
}

double stan_dev(vector<double> data) {
    double m = mean(data);
    double sd = 0;
    for (double d : data) {
        sd += pow(d - m, 2);
    }
    return sqrt(sd / data.size());
}

void results(int n, Point *start, Point *goal, Map &map) {
    vector<double> plan_time;
    vector<double> path_length;
    vector<double> nodes;
    
    for (int i = 0; i < n; i++) {
        time_t start_time = clock();
        auto plan = Planner::RRT_star(start, goal, map);
        time_t end_time = clock();
        
        plan_time.push_back((double)(end_time - start_time)/CLOCKS_PER_SEC*MS);
        path_length.push_back(plan.first.size() * 1.0);
        nodes.push_back(plan.second.num_vertices * 1.0);
    }
    
    cout << "Plan Time (ms): " << mean(plan_time) << " -+ " << stan_dev(plan_time) << endl;
    cout << "Path Length: " << mean(path_length) << " -+ " << stan_dev(path_length) << endl;
    cout << "# Nodes Sampled: " << mean(nodes) << " -+ " << stan_dev(nodes) << endl;
}

void example1(int argc, char *argv[], Map &map) {
    
    Point *start = new Point(-1, -3);
    Point *goal = new Point(9, 7);
    
    cout << "Start: " << *start << endl;
    cout << "Goal: " << *goal << endl;
    
//    results(100, start, goal, map);
    
   auto plan = Planner::RRT_star(start, goal, map);
   vector<Point*> path = plan.first;
   Graph<Point> graph = plan.second;

   Visualizer v;
   v.init(argc, argv);

   for (Obstacle obs : map.minkowski) {
     v.plot_obstacle(obs.convex_hull, blue);
   }

   for (Obstacle obs : map.obstacles) {
     v.plot_obstacle(obs.convex_hull, green);
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
  double robot_radius = 2;

  string filename = parse_args(argc, argv);
  cout << filename << endl;

  Map map = Map(robot_radius, filename);
  example1(argc, argv, map);
}

