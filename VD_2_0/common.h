#ifndef COMMON_H
#define COMMON_H



#include <vector>


typedef struct Vertex
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
//https://www.khronos.org/opengl/wiki/Vertex_Specification#Interleaved_arrays
typedef struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<UV> UV;
	std::vector<Face> faces;
};


#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

typedef struct Buffer
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

const float verticesUV[] = {
	// positions                   // texture coords
	 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,   // bottom left
};
static void Test_CreatBuffer(Buffer& buffer)
{

	glGenVertexArrays(1, &buffer.VAO);
	glGenBuffers(1, &buffer.VBO);

	glBindVertexArray(buffer.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
	//TODO: Do i need vector like this or normal array will do?
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUV), verticesUV, GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


void static CreateBufferWithPositionAndUVOnly(Mesh& mesh, Buffer& buffer)
{
	// Test_CreatBuffer(buffer);
	// return;

	glGenVertexArrays(1, &buffer.VAO);
	glGenBuffers(1, &buffer.VBO);

	glBindVertexArray(buffer.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer.VBO);
	//TODO: Do i need vector like this or normal array will do?

	//Pointer Size * Value size per
	size_t temp_TotalBufferSize = sizeof(std::vector<float>) * mesh.vertices.size() + 
		                          sizeof(std::vector<UV>)*mesh.UV.size();

	std::vector<float> tempBuffer;
	for (int i=0;i<mesh.vertices.size();i++)
	{
		tempBuffer.push_back(mesh.vertices.data()[i].x);
		tempBuffer.push_back(mesh.vertices.data()[i].y);
		tempBuffer.push_back(mesh.vertices.data()[i].z);
	}
	for (int i = 0; i < mesh.UV.size(); i++)
	{
		tempBuffer.push_back(mesh.UV.data()[i].u);
		tempBuffer.push_back(mesh.UV.data()[i].v);
	
	}

	
	glBufferData(GL_ARRAY_BUFFER, sizeof(std::vector<float>) * tempBuffer.size(), tempBuffer.data(), GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 
		                (void*) (sizeof(std::vector<float>)*(mesh.vertices.size()) ));


	/*
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesUV), verticesUV, GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	*/
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

//PACK UV AND POSTION IN ONE BUFFER


#endif

//TODO:
/*
- Check EBO
- Shader Logic
- Add Texture
- Convert to Arrays
- Add GLM and Transfomration logic
- Add Camera
*/