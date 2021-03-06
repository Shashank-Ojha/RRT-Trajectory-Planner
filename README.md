# RRT Trajectory Planner

Problem Statement:

Given a starting position (xs, ys), a target position (xt, yt), and a list of the convex hull points for each obstacle, find a feasible trajectory for an omnidirectional circular robot with radius r to follow to get to the target position avoiding obstacle collisions. 

Note, we've set the radius of the robot to 1.

RUNNING THE CODE:
  
    Compile by typing "make" on terminal
    Run by typing "./plan" on terminal
    
    The above runs the default map with RRT-Connect
    
    If you want to change the map and algo you can also provide two command line arguments.
    The usage is as follows
    
    ./plan [FILENAME] [ALGO]
      where Maps are in maps/ folder.
            Algo is 0 for RRT-Connect and 1 for RRT-Star.
            
    Example:   ./plan maps/map1.txt 1

CODE BASE:

- main.cpp
    - Contains the first file the planner runs. It parses user input and runs either RRT-Connect or RRT*
- Planner.cpp
    - Contains RRT-Connect and RRT* Algorithms
- Visualizer.cpp
    - Contains helper functions to visualize our maps


- utils/Graph.h
    - Contains graph data structure implementation
- utils/KDTree.cpp
    - Contains kd-tree data structure implementation
- utils/Map.cpp
    - Contains Map class to keep track of all information related to environment
- utils/Obstacle.cpp
    - Contains Obstacle class to keep track of all information related to an obstacle
- utils/Point.cpp
    - Contains Point class which is utilized throughout the code base
- utils/Search.h
    - Contains A* Search Function
