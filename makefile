all: compile link

compile: 
	g++ -Isrc -Isrc/include -c src/main.cpp 
	g++ -Isrc -Isrc/include -c src/textureManager.cpp 
	g++ -Isrc -Isrc/include -c src/spriteManager.cpp 
	g++ -Isrc -Isrc/include -c src/enemy.cpp 
	g++ -Isrc -Isrc/include -c src/enemytexture.cpp 
	g++ -Isrc -Isrc/include -c src/player.cpp 
	g++ -Isrc -Isrc/include -c src/animation.cpp 
	g++ -Isrc -Isrc/include -c src/levelone.cpp 

	

link: 
	g++ main.o textureManager.o spriteManager.o enemy.o player.o animation.o levelone.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system