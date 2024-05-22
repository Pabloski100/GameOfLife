sfmlapp: main.o gamegui.o game.o presets.o
	g++ main.o gamegui.o game.o presets.o -o main -lsfml-graphics -lsfml-window -lsfml-system -O2 -std=c++11 -larmadillo

main.o: main.cpp
	g++ -c main.cpp

gamegui.o: gamegui.cpp
	g++ -c gamegui.cpp

game.o: game.cpp
	g++ -c game.cpp

presets.o: presets.cpp presets.h
	g++ -c presets.cpp

clean:
	rm *.o