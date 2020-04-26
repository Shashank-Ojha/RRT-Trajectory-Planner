# RRT Trajectory Planner

Problem Statement:

Given a starting position (xs, ys), a target position (xt, yt), and a list of the convex hull points for each obstacle, find a feasible trajectory for an omnidirectional circular robot with radius r to follow to get to the target position avoiding obstacle collisions. 


RUNNING THE CODE:
  
    Compile by typing "make" on terminal
    Run by typing "./plan" on terminal

CODE BASE:

- main.cpp
- Planner.cpp
- Visualizer.cpp


- utils/Graph.h
- utils/KDTree.cpp
- utils/Map.cpp
- utils/Obstacle.cpp
- utils/Point.cpp
- utils/Search.h
