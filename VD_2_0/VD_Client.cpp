#include "VD_Client.h"
#include <iostream>


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



void VD_Client::Init()
{

   square.vertices.push_back(Vertex{ 0,0,0 });
   square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });
   square.vertices.push_back(Vertex{ 0.0f,1.0f,0 });

	square.vertices.push_back(Vertex{ 0,0,0 });
	square.vertices.push_back(Vertex{1.0f,0.0f,0});
	square.vertices.push_back(Vertex{ 1.0f,1.0f,0 });

	square.faces.push_back(Face{ 0,1,2 });

    
	 CreateBufferWithPositionOnly(square, triangleRenderer);

     ResourceManager::LoadShaderWithHardCoded(C_SimpleShader, vertexShaderSource, fragmentShaderSource);
     ResourceManager::LoadTexture(".//res//Test.png", true, "TestTexture");
     ResourceManager::LoadTexture(".//res//Test.png", true, "TestTexture");
     ResourceManager::LoadShader("ShaderWithTexture",".//res//Shaders//Simple.vert",".//res//Shaders//Simple.frag");

     
     //HARDCODED 
	/**/
        // build and compile our shader program
    // ------------------------------------
    // vertex shader
     /*
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
   shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
	*/
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
    ResourceManager::GetShader(C_SimpleShader).Use();
    glBindVertexArray(triangleRenderer.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, square.vertices.size());
}
