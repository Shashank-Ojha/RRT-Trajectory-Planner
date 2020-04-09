CFLAGS = -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa

planner: main.o Point.o Obstacle.o Graph.o Map.o # Visualizer.o
	g++ $(CFLAGS) main.cpp -o planner

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

Point.o: Point.cpp
	g++ $(CFLAGS) -c Point.cpp

Obstacle.o: Obstacle.cpp
	g++ $(CFLAGS) -c Obstacle.cpp

Graph.o: Graph.cpp
	g++ $(CFLAGS) -c Graph.cpp

Map.o: Map.cpp
	g++ $(CFLAGS) -c Map.cpp

# Visualizer.o: Visualizer.cpp
# 	g++ -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa -c Visualizer.cpp

clean:
	rm *.o planner
