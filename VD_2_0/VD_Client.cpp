#include "VD_Client.h"



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* C_SimpleShader = "SimpleShader";

//unsigned int textureID;
void VD_Client::Init()
{

   square.vertices.push_back(Vertex{ 0,0,0 });
   square.UV.push_back(UV{ 0, 0 });
   square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });
   square.UV.push_back(UV{ 1, 1 });
   square.vertices.push_back(Vertex{ 0.0f,1.0f,0 });
   square.UV.push_back(UV{ 1, 0 });

	square.vertices.push_back(Vertex{ 0,0,0 });
    square.UV.push_back(UV{ 0, 0 });
	square.vertices.push_back(Vertex{1.0f,0.0f,0});
    square.UV.push_back(UV{ 0, 1 });
	square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });
    square.UV.push_back(UV{ 1, 1 });

	square.faces.push_back(Face{ 0,1,2 });

    
	// CreateBufferWithPositionOnly(square, triangleRenderer);
    // Test_CreatBuffer(triangleRenderer);
    CreateBufferWithPositionAndUVOnly(square,triangleRenderer);

    // ResourceManager::LoadShaderWithHardCoded(C_SimpleShader, vertexShaderSource, fragmentShaderSource);
     ResourceManager::LoadTexture(".//res//Test.jpg", false, "TestTexture");
   
     ResourceManager::LoadShader("ShaderWithTexture",".//res//Shaders//Simple.vert",".//res//Shaders//Simple.frag");


}

void VD_Client::Input()
{
}

void VD_Client::Update()
{
}

void VD_Client::Render()
{
   // glUseProgram(shaderProgram);

    glActiveTexture(GL_TEXTURE0);
    ResourceManager::GetTexture("TestTexture").Bind();

  //  glBindTexture(GL_TEXTURE_2D, textureID);

    ResourceManager::GetShader("ShaderWithTexture").Use();
    glBindVertexArray(triangleRenderer.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, square.vertices.size());
}
