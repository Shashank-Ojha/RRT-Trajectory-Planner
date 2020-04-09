planner: main.o Point.o Obstacle.o Graph.o # Visualizer.o
	g++ -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa main.cpp -o planner

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

Point.o: Point.cpp
	g++ -std=c++17 -c Point.cpp

Obstacle.o: Obstacle.cpp
	g++ -std=c++17 -c Obstacle.cpp

Graph.o: Graph.cpp
	g++ -std=c++17 -c Graph.cpp

# Visualizer.o: Visualizer.cpp
# 	g++ -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa -c Visualizer.cpp

clean:
	rm *.o planner
