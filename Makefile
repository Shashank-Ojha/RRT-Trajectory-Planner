
APP_NAME = plan

OBJS = main.o \
			 utils/Graph.o \
			 utils/KDTree.o \
			 utils/Map.o \
			 utils/Obstacle.o \
			 utils/Point.o \
			 Planner.o \
			 Visualizer.o

CXX = g++
CXXFLAGS = -std=c++17 -framework GLUT -framework OpenGL -framework Cocoa

$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(APP_NAME)

# Create Object file for everything in utils dir
utils/%.o: utils/%.cpp utils/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Object file for everything in current dir
%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

clean:
	rm *.o utils/*.o plan
