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

#include "../../Point.cpp"
#include "../../Graph.cpp"

using namespace std;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define SCALE 0.05

struct Color {
    GLbyte r, g, b;
};

void plot_point(Point &p, Color &node_color) {
    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(node_color.r, node_color.g, node_color.b);
    glVertex2f(p.x, p.y);
    glEnd();
}

void plot_segment(Point &p1, Point &p2, Color &node_color, Color &edge_color)
{
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

void plot_trajectory(vector<Point> &trajectory, Color &node_color, Color &edge_color) {
    glBegin(GL_LINE_STRIP);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : trajectory) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
    
    // plot points
    for (auto p : trajectory) {
        plot_point(p, node_color);
    }
}

void plot_graph(Graph<Point> &graph, Color &node_color, Color &edge_color) {
    unordered_map<Point*, unordered_set<Point*>>::iterator it = graph.edges.begin();
    while (it != graph.edges.end()) {
        Point *p1 = it->first;
        for (auto p2 : it->second) {
            plot_segment(*p1, *p2, node_color, edge_color);
        }
    }
}

void plot_obstacle(vector<Point> &obstacles, Color &edge_color) {
    glBegin(GL_POLYGON);
    glColor3f(edge_color.r, edge_color.g, edge_color.b);
    for (auto p : obstacles) {
        glVertex2f(p.x, p.y);
    }
    glEnd();
}


void rescale(Point &p) {
    p.x *= SCALE;
    p.y *= SCALE;
}

void testExample() {
    Color black = {0, 0, 0};
    Color red = {1, 0, 0};
    Color green = {0, 1, 0};
    Color blue = {0, 0, 1};
    
    Point *root = new Point(0, 0);
    Point *A = new Point(-3.0, -7.0);
    Point *B = new Point(3, 7);
    rescale(*A);
    rescale(*B);
    
    Point *p1 = new Point(2.0, 1.0);
    Point *p2 = new Point(0.0, 3.0);
    Point *p3 = new Point(1.0, 4.3);
    Point *p4 = new Point(6.0, 2.2);
    vector<Point> obs{*p1, *p2, *p3, *p4};
    for (auto &p : obs) {
        rescale(p);
    }
    Graph<Point> graph(root);
    graph.add_edge(root, A);
    graph.add_edge(root, B);
    
    //Plot examples
    plot_obstacle(obs, green);
    plot_point(*A, blue);
    plot_point(*B, red);
//    plot_segment(*root, *B, blue, red);
//    plot_segment(*root, *A, green, red);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    testExample();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);

    // set up size and display mode
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutInitWindowPosition(100, 150);
    glutInitDisplayMode(GLUT_RGB);
    
    // create and set up window
    glutCreateWindow("RRT Trajectory Planner");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
    return 0;
}
