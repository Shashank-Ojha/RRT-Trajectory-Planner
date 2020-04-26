/*
    Plot initial point, final point, obstacles and trajectory
 
    On Xcode, Run Visualizer project
 */

#define GL_SILENCE_DEPRECATION

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

void Visualizer::plot_circle(Point &p, double radius, Color &node_color) {
    double x = rescale(p.x);
    double y = rescale(p.y);
    double r = rescale(radius);
    double angle, x1, y1;
    
    glPointSize(10);
    glBegin(GL_POLYGON);
    glColor3f(node_color.r, node_color.g, node_color.b);
    for (angle = 0; angle < 360.0; angle += 1.0) {
        x1 = x + cos(angle) * r;
        y1 = y + sin(angle) * r;
        glVertex2f(x1, y1);
    }
    glEnd();
}

void Visualizer::plot_point(Point &p, Color &node_color) {
    double x = rescale(p.x);
    double y = rescale(p.y);
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(node_color.r, node_color.g, node_color.b);
    glVertex2f(x, y);
    glEnd();
}

void Visualizer::plot_segment(Point &p1, Point &p2, Color &node_color, Color &edge_color)
{
    double x1 = rescale(p1.x);
    double y1 = rescale(p1.y);
    double x2 = rescale(p2.x);
    double y2 = rescale(p2.y);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    glVertex2f(x1, y1); // origin of the line
    glVertex2f(x2, y2); // ending point of the line
    glEnd();
    
    // plot points
    plot_point(p1, node_color);
    plot_point(p2, node_color);
}

void Visualizer::plot_trajectory(vector<Point*> &trajectory, Color &node_color, Color &edge_color) {
    glBegin(GL_LINE_STRIP);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : trajectory) {
        double x = rescale(p->x);
        double y = rescale(p->y);
        glVertex2f(x, y);
    }
    glEnd();
    
    // plot points
    for (auto p : trajectory) {
        plot_point(*p, node_color);
    }
}

void Visualizer::plot_graph(Graph<Point> &graph, Color &node_color, Color &edge_color) {
    for (auto pair : graph.adj_list) {
        Point *p1 = pair.first;
        unordered_set<Point*> set = pair.second;
        for (auto *p2 : set) {
            double x1 = rescale(p1->x);
            double y1 = rescale(p1->y);
            double x2 = rescale(p2->x);
            double y2 = rescale(p2->y);
            plot_segment(*p1, *p2, node_color, edge_color);
        }
    }
}

void Visualizer::plot_obstacle(vector<Point> &obstacles, Color &edge_color) {
    glBegin(GL_POLYGON);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : obstacles) {
        double x = rescale(p.x);
        double y = rescale(p.y);
        glVertex2f(x, y);
    }
    glEnd();
}

void Visualizer::display() {
    glClear(GL_COLOR_BUFFER_BIT);
}

double Visualizer::rescale(double p) {
    return p * SCALE;
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
