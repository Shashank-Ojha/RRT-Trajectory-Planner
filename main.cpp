#include <iostream>
#include <vector>

#include "utils/Graph.h"
#include "utils/KDTree.h"
#include "utils/Map.h"
#include "utils/Obstacle.h"
#include "utils/Point.h"

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

int main(int argc, char *argv[]) {

  Color black = {0, 0, 0};

  string filename = parse_args(argc, argv);
  cout << filename << endl;

  Map map = Map(filename);
  
  // Visualizer v;
  // v.init(argc, argv);
  // v.plot_obstacle(polygon, black);
  // v.run();
}
