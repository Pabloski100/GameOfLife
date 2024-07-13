sfmlapp: main.o gamegui.o game.o presets.o utils.o
	g++ main.o gamegui.o game.o presets.o utils.o -o main -lsfml-graphics -lsfml-window -lsfml-system -O2 -std=c++17 -larmadillo

main.o: main.cpp
	g++ -c main.cpp

gamegui.o: gamegui.cpp
	g++ -c gamegui.cpp

game.o: game.cpp
	g++ -c game.cpp

presets.o: presets.cpp presets.hpp
	g++ -c presets.cpp

utils.o: utils.cpp
	g++ -c utils.cpp

clean:
	rm *.o