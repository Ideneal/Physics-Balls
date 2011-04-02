ball: ball.cpp
	g++ -c ball.cpp
	g++ -c system.cpp
	g++ -o game system.o ball.o main.cpp -lSDL -lSDL_image
