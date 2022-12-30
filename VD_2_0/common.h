#ifndef COMMON_H
#define COMMON_H

#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <vector>


 struct Vertex
{
	float x, y, z;
} ;

 typedef struct UV
{
	float u, v;
} ;

typedef struct Face
{
	unsigned int i1,i2,i3;
} ;

typedef struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
};


#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

struct Buffer
{
	unsigned VAO, VBO;
};

const float vertices1[] = {
	-0.5f, -0.5f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, // right 
	 0.0f,  0.5f, 0.0f  // top   
};

void static CreateBufferWithPositionOnly(Mesh &mesh, Buffer &buffer)
{

	glGenVertexArrays(1, &buffer.VAO);
	glGenBuffers(1, &buffer.VBO);

	glBindVertexArray(buffer.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
	//TODO: Do i need vector like this or normal array will do?
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::vector<float>) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
}

#endif