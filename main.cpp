/*
  Temporary file to test code 

  Compile using: g++ main.cpp
  Run using: ./a.out
*/

#include <iostream>

#include "Point.cpp"
#include "Graph.cpp"

using namespace std;

int main() {

  Point *root = new Point(0, 0);
  Graph<Point> graph(root);

  Point *A = new Point(1, 5);
  Point *B = new Point(2.3, 4.7);

  graph.add_edge(root, A);
  graph.add_edge(root, B);

  cout << graph;
}