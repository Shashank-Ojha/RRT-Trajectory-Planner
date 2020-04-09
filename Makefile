
APP_NAME = planner

OBJS = main.o \
		   utils/Point.o \
			 utils/Obstacle.o \
			 utils/Graph.o \
			 utils/Map.o \
			 Visualizer.o

CXX = g++
CXXFLAGS = -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa

$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o planner

# Create Object file for everything in utils dir
utils/%.o: utils/%.cpp utils/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Object file for everything in current dir
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm *.o utils/*.o planner
