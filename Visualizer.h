/*
    Plot initial point, final point, obstacles and trajectory
 
    On Xcode, Run Visualizer project
 */
#ifndef __VISUALIZER_H
#define __VISUALIZER_H

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <vector>

#include "utils/Point.h"
#include "utils/Graph.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define SCALE 0.05

struct Color {
    GLbyte r, g, b;
};

class Visualizer {
    
  public:
    Visualizer();

    void plot_point(Point &p, Color &node_color);
    void plot_segment(Point &p1, Point &p2, Color &node_color, Color &edge_color);
    void plot_trajectory(vector<Point> &trajectory, Color &node_color, Color &edge_color);
    void plot_graph(Graph<Point> &graph, Color &node_color, Color &edge_color);
    void plot_obstacle(vector<Point> &obstacles, Color &edge_color);
    
    static void display() {
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void rescale(Point &p);
    void init(int argc, char *argv[]);
    void run();
};

#endif /* __VISUALIZER_H */
