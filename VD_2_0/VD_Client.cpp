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

     ResourceManager::LoadShader("ShaderWithTextureAndTransform", ".//res//Shaders//Simple_Transform.vert", ".//res//Shaders//Simple_Transform.frag");
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

    ResourceManager::GetShader("ShaderWithTextureAndTransform").Use();
    glBindVertexArray(triangleRenderer.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    unsigned int transformLoc = glGetUniformLocation(ResourceManager::GetShader("ShaderWithTextureAndTransform").GetID(), "transform");
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    glDrawArrays(GL_TRIANGLES, 0, square.vertices.size());
}
