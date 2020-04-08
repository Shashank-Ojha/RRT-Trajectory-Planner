/*
  Temporary file to test code 

  Compile using: g++ main.cpp
  Run using: ./a.out
*/

#include <iostream>

#include "Point.cpp"

using namespace std;

int main() {
  Point x(1, 1);
  Point y(3, 4);

  cout << x.dist(y) << endl;
}