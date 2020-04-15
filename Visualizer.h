/**
 *  @file Visualizer.h
 *  @brief Defines a class to plot points, obstacles, graphs, and trajectories
 *
 *  @author Shashank Ojha (shashano)
 *  @author Serris Lew (snlew)
 *  @author David Bick (dbick)
 *  @bug No known bugs.
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

/* Constants about our Display Screen */
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define SCALE 0.05

/* Struct to keep track of Colors */
struct Color {
    GLbyte r, g, b;
};

class Visualizer {
    
  public:
    /* Constructors */
    Visualizer();

    /* Function Prototypes */
    void plot_point(Point &p, Color &node_color);
    void plot_segment(Point &p1, Point &p2, Color &node_color, Color &edge_color);
    void plot_trajectory(vector<Point*> &trajectory, Color &node_color, Color &edge_color);
    void plot_graph(Graph<Point> &graph, Color &node_color, Color &edge_color);
    void plot_obstacle(vector<Point> &obstacles, Color &edge_color);
    
    static void display();

    double rescale(double p);
    void init(int argc, char *argv[]);
    void run();
};

#endif /* __VISUALIZER_H */
