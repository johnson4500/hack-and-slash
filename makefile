all: compile link

compile: 
	g++ -Isrc/include -c main.cpp 
	g++ -Isrc/include -c textureManager.cpp 
	g++ -Isrc/include -c spriteManager.cpp 
	g++ -Isrc/include -c enemy.cpp 
	g++ -Isrc/include -c enemytexture.cpp 

	

link: 
	g++ main.o textureManager.o spriteManager.o enemy.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system