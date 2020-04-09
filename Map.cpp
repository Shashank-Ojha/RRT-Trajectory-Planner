
#ifndef __MAP_CPP
#define __MAP_CPP

#include <iostream>
#include <vector>

#include "Obstacle.cpp"

using namespace std;

class Map
{
  public:
    int num_obstacles;
    vector<Obstacle> obstacles;

    Map() {
      this->num_obstacles = 0;
      this->obstacles = vector<Obstacle>();
    }

    Map(vector<Obstacle> obstacles) {
      this->num_obstacles = obstacles.size();
      this->obstacles = vector<Obstacle>(obstacles);
    }

    void add_obstacle(Obstacle &obs) {
      this->num_obstacles += 1;
      this->obstacles.push_back(obs);
    }

    bool is_freespace(Point &p) {
      for(Obstacle &obs : this->obstacles) {
        if(obs.collides(p)) {
          return false;
        }
      }
      return true;
    }
};

#endif /* __MAP_CPP */
