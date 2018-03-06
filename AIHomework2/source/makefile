
output: main.o board_space.o map_space.o location.o
	g++ main.o board_space.o map_space.o location.o -o output.exe
	
main.o: main.cpp
	g++ -c main.cpp 
	
board_space.o: board_space.cpp board_space.h
	g++ -c board_space.cpp

map_space.o: map_space.cpp map_space.h
	g++ -c map_space.cpp

location.o: location.cpp location.h
	g++ -c location.cpp

clean:
	rm *.o output