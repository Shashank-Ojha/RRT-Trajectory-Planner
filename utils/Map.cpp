#include <iostream>
#include <vector>

#include "Map.h"
#include "Obstacle.h"
#include "Point.h"

using namespace std;

Map::Map() {
  this->num_obstacles = 0;
  this->obstacles = vector<Obstacle>();
}

Map::Map(vector<Obstacle> obstacles) {
  this->num_obstacles = obstacles.size();
  this->obstacles = vector<Obstacle>(obstacles);
}

void Map::add_obstacle(Obstacle &obs) {
  this->num_obstacles += 1;
  this->obstacles.push_back(obs);
}

bool Map::is_freespace(Point &p) {
  for(Obstacle &obs : this->obstacles) {
    if(obs.collides(p)) {
      return false;
    }
  }
  return true;
}