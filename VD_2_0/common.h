#ifndef COMMON_H
#define COMMON_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

typedef struct Vertex
{
	float x, y, z;
};

 typedef struct UV
{
	float u, v;
} ;

typedef struct Face
{
	unsigned int i1,i2,i3;
};

typedef struct Transformation
{
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Size;

};

//https://www.khronos.org/opengl/wiki/Vertex_Specification#Interleaved_arrays
typedef struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<UV> UV;
	std::vector<Face> faces;
	std::vector<Vertex> normal;
	Transformation transform;
};


#include "include/glad/glad.h"
#include "include/GLFW/glfw3.h"

typedef struct Buffer
{
	unsigned VAO, VBO;// TODO: Should i remove vbo since vao is more important ?
	 
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

	if (mesh.vertices.size() != mesh.UV.size())
	{
		std::cout << "Error:UY count and Vertices Count different:UV:"
			<< mesh.vertices.size()<<",Vertices:"<< mesh.UV.size();
	}
	// x y z u v (layout)
	std::vector<float> tempBuffer;
	for (int i= 0;i< mesh.vertices.size(); i++)
	{
		if (i < mesh.vertices.size())
		{
			tempBuffer.push_back(mesh.vertices.data()[i].x);
			tempBuffer.push_back(mesh.vertices.data()[i].y);
			tempBuffer.push_back(mesh.vertices.data()[i].z);
		}

		if (i < mesh.UV.size())
		{
			tempBuffer.push_back(mesh.UV.data()[i].u);
			tempBuffer.push_back(mesh.UV.data()[i].v);
		}
	}
	

	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tempBuffer.size(), &tempBuffer.front(), GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	// Looks like it takes row by row so mention row size 5*float and starting point in them
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 
		                (void*) ( sizeof(float)*3) );


	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

//PACK UV AND POSTION IN ONE BUFFER

void static CreateBufferWithPositionUVNormalOnly(Mesh& mesh, Buffer& buffer)
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
		sizeof(std::vector<UV>) * mesh.UV.size();

	if (mesh.vertices.size() != mesh.UV.size())
	{
		std::cout << "Error:UY count and Vertices Count different:UV:"
			<< mesh.vertices.size() << ",Vertices:" << mesh.UV.size();
	}
	// x y z u v (layout)
	std::vector<float> tempBuffer;
	for (int i = 0; i < mesh.vertices.size(); i++)
	{
		if (i < mesh.vertices.size())
		{
			tempBuffer.push_back(mesh.vertices.data()[i].x);
			tempBuffer.push_back(mesh.vertices.data()[i].y);
			tempBuffer.push_back(mesh.vertices.data()[i].z);
		}

		if (i < mesh.UV.size())
		{
			tempBuffer.push_back(mesh.UV.data()[i].u);
			tempBuffer.push_back(mesh.UV.data()[i].v);
		}
		if (i < mesh.normal.size())
		{
			tempBuffer.push_back(mesh.normal.data()[i].x);
			tempBuffer.push_back(mesh.normal.data()[i].y);
			tempBuffer.push_back(mesh.normal.data()[i].z);
		}
	}



	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tempBuffer.size(), &tempBuffer.front(), GL_STATIC_DRAW);
	// 2. copy our vertices array in a buffer for OpenGL to use
	// 3. then set our vertex attributes pointers
	// Looks like it takes row by row so mention row size 5*float and starting point in them
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//UV
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*)(sizeof(float) * 3));
	//noraml
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
		(void*)(sizeof(float) * 5));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

#endif

//TODO:
/* 
* 8_1_2023
- Check EBO - defferemt
- Shader Logic - ok
- Add Texture -ok
- Convert to Array- oks
- Add GLM and Transfomration logic - pending
- Add Camera - pending
*/