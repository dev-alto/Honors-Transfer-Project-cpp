all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp Boid.cpp Renderer.cpp FlockSystem.cpp Vector.cpp AABB.cpp -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2