### variables ##############

CXX        = g++
CXXFLAGS   = -g -Wall -fpic
OBJECTS    = Main.o Game.o Entity.o InnerWorld.o Npc.o SceneNode.o SpriteNode.o
LIBRARY    = -lsfml-graphics -lsfml-window -lsfml-system 

############################ 

output: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LIBRARY) -o output $(OBJECTS) 

Main.o: src/Main.cpp
	$(CXX) $(CXXFLAGS) -c src/Main.cpp

Game.o: src/Game.cpp src/Game.hpp
	$(CXX) $(CXXFLAGS) -c src/Game.cpp

Entity.o: src/Entity.cpp src/Entity.hpp
	$(CXX) $(CXXFLAGS) -c src/Entity.cpp

InnerWorld.o: src/InnerWorld.cpp src/InnerWorld.hpp
	$(CXX) $(CXXFLAGS) -c src/InnerWorld.cpp

Npc.o: src/Npc.cpp src/Npc.hpp
	$(CXX) $(CXXFLAGS) -c src/Npc.cpp

SceneNode.o: src/SceneNode.cpp src/SceneNode.hpp
	$(CXX) $(CXXFLAGS) -c src/SceneNode.cpp

SpriteNode.o: src/SpriteNode.cpp src/SpriteNode.hpp
	$(CXX) $(CXXFLAGS) -c src/SpriteNode.cpp
############################

# To prevent make from getting confused by an actual file called clean, me may use .PHONY:
# The "-" in -rm causes make to continue in spite of errors from rm
.PHONY: clean
clean:
	-rm $(OBJECTS) output 

