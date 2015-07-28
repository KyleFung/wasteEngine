INC=-I./Include/ImageMagick/ -I./Include/ -I./Include/assimp/
LINK=-lMagick++ -lGL -lglut -lGLEW -lassimp
COMMON=./Common/Texture.cpp ./Common/utils.cpp ./Common/Pipeline.cpp ./Common/Camera.cpp
RENDERER=./Renderer/Mesh.cpp ./Renderer/Shader.cpp ./Renderer/Technique.cpp

all:
	g++ main.cpp $(COMMON) $(RENDERER) $(LINK) $(INC) -g -o Build/test
