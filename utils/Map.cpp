/**
 *  @file Map.cpp
 *  @brief Implements the class Map defined in Map.h
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
 */

#include <vector>
#include <fstream>

#include "Map.h"
#include "Obstacle.h"
#include "Point.h"

using namespace std;

/**
 * @brief Default Map constructor.
 *
 * @return Map containing no obstacles.
 */
Map::Map() {
  this->num_obstacles = 0;
  this->obstacles = vector<Obstacle>();
}

/**
 * @brief Map constructor given a set of obstacles.
 *
 * @param obstacles A vector of all obstacles in map.
 * @return Map containing all obstacles given.
 */
Map::Map(const vector<Obstacle> obs) {
  this->num_obstacles = obs.size();
  this->obstacles = vector<Obstacle>(obs);
}

/**
 * @brief Map constructor that reads data from file.
 *
 * @param filename The file to read from.
 * @return Map containing all data given in file.
 */
Map::Map(const string filename) {
  ifstream infile;
  infile.open(filename);

  if (!infile) {
    cout << "Unable to open file!" << endl;
    exit(1); // terminate with error
  }

  infile >> this->height;
  infile >> this->width;

  infile >> this->num_obstacles;

  for (int i = 0; i < this->num_obstacles; i++) {
    vector<Point> polygon;
    int n;
    infile >> n;
    for (int j = 0; j < n; j++) {
      float x, y;
      infile >> x;
      infile >> y;
      polygon.push_back(Point(x, y));
    } 
    this->obstacles.push_back(Obstacle(polygon));
    polygon.clear();    
  }
}

/**
 * @brief Adds the given obstacle to the map.
 *
 * @param obstacle An Obstacle.
 * @return Void.
 */
void Map::add_obstacle(const Obstacle &o) {
  this->num_obstacles += 1;
  this->obstacles.push_back(o);
}

/**
 * @brief Checks if the given point collides with any of the obstacles in the
 * Map.
 *
 * @param p A point.
 * @return True if it doesn't collid with any obstacles and False otherwise.
 */
bool Map::is_freespace(const Point &p) const {
  for(const Obstacle &obs : this->obstacles) {
    if(obs.collides(p)) {
      return false;
    }
  }
  return true;
}