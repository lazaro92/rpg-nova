### variables ##############

CXX        = g++
CXXFLAGS   = -g -Wall -fpic
OBJECTS    = main.o Game.o ResourceHolder.o
LIBRARY    = -lsfml-graphics -lsfml-window -lsfml-system 

############################ 

output: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBRARY) -o output $(OBJECTS) 

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

Game.o: src/Game.cpp src/Game.hpp
	$(CXX) $(CXXFLAGS) -c src/Game.cpp

ResourceHolder.o: src/ResourceHolder.cpp src/ResourceHolder.hpp
	$(CXX) $(CXXFLAGS) -c src/ResourceHolder.cpp

############################

# To prevent make from getting confused by an actual file called clean, me may use .PHONY:
# The "-" in -rm causes make to continue in spite of errors from rm
.PHONY: clean
clean:
	-rm $(OBJECTS) output 

