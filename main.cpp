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
#define RRT_CONNECT 0
#define RRT_STAR 1

using namespace std;
string DEFAULT_MAP = "maps/map2.txt";


Color black = {0, 0, 0};
Color red = {1, 0, 0};
Color blue = {0, 0, 1};
Color green = {0, 1, 0};

void usage() {
  cout << "Usage: ./plan [FILENAME] [ALGO]" << endl;
  cout << "\t Maps are in maps/ folder." << endl;
  cout << "\t Algo is 0 for RRT-Connect and 1 for RRT-Star." << endl;
  exit(0);
}

pair<int, string> parse_args(int argc, char *argv[]) {
  string filename = DEFAULT_MAP;
  int chosen_algo = RRT_CONNECT;

  if (argc == 1) {
    return {chosen_algo, filename};
  } else if (argc == 3) {
    filename = string(argv[1]);
    chosen_algo = atoi(argv[2]);
    if(chosen_algo != RRT_CONNECT && chosen_algo != RRT_STAR) {
      usage();
    }
    return {chosen_algo, filename};
  } 
  usage();
  exit(0);
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

pair<vector<Point*>, Graph<Point>> get_plan(Point *start, Point *goal, Map &map, int algo) {
  if(algo == RRT_CONNECT) {
    return Planner::RRT_connect(start, goal, map);
  }
  return Planner::RRT_star(start, goal, map);
}

void example1(int argc, char *argv[], Map &map, double robot_radius, int algo) {
    
    Point *start = new Point(-1, -3);
    Point *goal = new Point(9, 7);
    
    cout << "Start: " << *start << endl;
    cout << "Goal: " << *goal << endl;
    
//    results(100, start, goal, map);

   auto plan = get_plan(start, goal, map, algo);

   vector<Point*> path = plan.first;
   Graph<Point> graph = plan.second;

   Visualizer v;
   v.init(argc, argv);

   // Plot expansion of obstacles
//   for (Obstacle obs : map.minkowski) {
//     v.plot_obstacle(obs.convex_hull, blue);
//   }

   // Plot obstacles
   for (Obstacle obs : map.obstacles) {
     v.plot_obstacle(obs.convex_hull, red);
   }

   v.plot_graph(graph, green, green);
   v.plot_trajectory(path, black, black);
   v.plot_circle(*start, robot_radius, blue);
   v.plot_point(*goal, blue);

   v.run();
}

int main(int argc, char *argv[]) {
  /* Set random seed */
  srand((unsigned) time(0));
  double robot_radius = 2;

  auto args = parse_args(argc, argv);
  int algo = args.first;
  string filename = args.second;

  Map map = Map(robot_radius, filename);
  example1(argc, argv, map, robot_radius, algo);
}

