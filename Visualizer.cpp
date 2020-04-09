/*
    Plot initial point, final point, obstacles and trajectory
 
    On Xcode, Run Visualizer project
 */

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GLUT/glut.h>
#include <vector>

#include "utils/Point.h"
#include "utils/Graph.h"

#include "Visualizer.h"

using namespace std;

Visualizer::Visualizer() {}

void Visualizer::plot_point(Point &p, Color &node_color) {
    rescale(p);
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(node_color.r, node_color.g, node_color.b);
    glVertex2f(p.x, p.y);
    glEnd();
}

void Visualizer::plot_segment(Point &p1, Point &p2, Color &node_color, Color &edge_color)
{
    rescale(p1);
    rescale(p2);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    glVertex2f(p1.x, p1.y); // origin of the line
    glVertex2f(p2.x, p2.y); // ending point of the line
    glEnd();
    
    // plot points
    plot_point(p1, node_color);
    plot_point(p2, node_color);
}

void Visualizer::plot_trajectory(vector<Point> &trajectory, Color &node_color, Color &edge_color) {
    glBegin(GL_LINE_STRIP);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : trajectory) {
        rescale(p);
        glVertex2f(p.x, p.y);
    }
    glEnd();
    
    // plot points
    for (auto p : trajectory) {
        plot_point(p, node_color);
    }
}

void Visualizer::plot_graph(Graph<Point> &graph, Color &node_color, Color &edge_color) {
    // need to rescale points after given array of points
    unordered_map<Point*, unordered_set<Point*>>::iterator it = graph.edges.begin();
    while (it != graph.edges.end()) {
        Point *p1 = it->first;
        for (auto p2 : it->second) {
            plot_segment(*p1, *p2, node_color, edge_color);
        }
    }
}

void Visualizer::plot_obstacle(vector<Point> &obstacles, Color &edge_color) {
    glBegin(GL_POLYGON);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : obstacles) {
        rescale(p);
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

void Visualizer::display() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Visualizer::rescale(Point &p) {
    p.x *= SCALE;
    p.y *= SCALE;
}

void Visualizer::init(int argc, char *argv[]) {
    glutInit(&argc, argv);

    // set up size and display mode
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutInitDisplayMode(GLUT_RGB);
    
    // create and set up window
    glutCreateWindow("RRT Trajectory Planner");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(display);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Visualizer::run() {
    glFlush();
    glutMainLoop();
}