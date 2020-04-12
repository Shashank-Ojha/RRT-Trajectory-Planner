#include <iostream>
#include <vector>

#include "utils/Graph.h"
#include "utils/KDTree.h"
#include "utils/Map.h"
#include "utils/Obstacle.h"
#include "utils/Point.h"

#include "Visualizer.h"

using namespace std;

int main(int argc, char *argv[]) {

  /*
  // Graph<Point> graph(root);
  Color black = {0, 0, 0};
  Point A(0, 0);
  Point B(2, 0);
  Point C(1.95, 1);
  Point D(2, 2);

  vector<Point> polygon;
  polygon.push_back(A);
  polygon.push_back(B);
  // polygon.push_back(C);
  polygon.push_back(D);

  Obstacle obs(polygon);
  Map m;
  m.add_obstacle(obs);
  cout << m.is_freespace(C) << endl;

  // graph.add_edge(root, A);
  // graph.add_edge(root, B);

  // cout << graph;

  Visualizer v;
  v.init(argc, argv);
  v.plot_obstacle(polygon, black);
  v.run();

  */
  Point *init_pt = new Point(23, 24);
  KDTree *kd_tree = new KDTree(init_pt);
  kd_tree->insert_node(new Point(100, 101));
  kd_tree->insert_node(new Point(100, 100));
  kd_tree->insert_node(new Point(105, 90));
  kd_tree->insert_node(new Point(100, 100));
  kd_tree->insert_node(new Point(20, 24));
  kd_tree->insert_node(new Point(20, 20));
  kd_tree->insert_node(new Point(100, 102));
  cout << kd_tree->find_node(new Point(100, 102)) << "\n";
  cout << kd_tree->find_node(new Point(42, 42)) << "\n";

  kd_tree->print_inorder();

}
