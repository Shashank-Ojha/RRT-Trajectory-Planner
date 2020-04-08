/*
  Temporary file to test code 

  Compile using: g++ main.cpp -std=c++17
  Run using: ./a.out
*/

#include <iostream>
#include <vector>

#include "Point.cpp"
#include "Graph.cpp"
#include "Obstacle.cpp"


using namespace std;

int main() {

  // Graph<Point> graph(root);

  Point A(0, 0);
  Point B(2, 0);
  Point C(2.01, 1);
  Point D(2, 2);

  vector<Point> polygon;
  polygon.push_back(A);
  polygon.push_back(B);
  // polygon.push_back(C);
  polygon.push_back(D);

  Obstacle obs(polygon);
  cout << obs.collides(C) << endl;

  // graph.add_edge(root, A);
  // graph.add_edge(root, B);

  // cout << graph;
}