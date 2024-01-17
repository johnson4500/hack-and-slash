all: compile link

compile: 
	g++ -Isrc/include -c main.cpp 
	g++ -Isrc/include -c textureManager.cpp 
	g++ -Isrc/include -c spriteManager.cpp 
	

link: 
	g++ main.o textureManager.o spriteManager.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system