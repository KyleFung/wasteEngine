INC=-I./Include/ImageMagick/ -I./Include/ -I./Include/assimp/
LINK=-lMagick++ -lGL -lglut -lGLEW -lassimp
COMMON=./Common/Texture.cpp ./Common/utils.cpp ./Common/Pipeline.cpp ./Common/Camera.cpp ./Common/Entity.cpp
RENDERER=./Renderer/Mesh.cpp ./Renderer/LoadedMesh.cpp ./Renderer/GeneratedMesh.cpp ./Renderer/Shader.cpp ./Renderer/Technique.cpp

all:
	g++ main.cpp $(COMMON) $(RENDERER) $(LINK) $(INC) -g -o Build/test
