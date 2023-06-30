#include "Shader.h"
#include <iostream>

Shader::Shader()
{
}
void Shader::Compile(const char* vertexSource, const char* fragmentSource)
{
    unsigned int sVertex, sFragment, gShader;
    // vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");

    // shader program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
 
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);

}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}
void Shader::Use()
{
	glUseProgram(ID);
}

 int Shader::GetID()
{
     return ID;
}

 void Shader::SetVec3(const char* name, glm::vec3& value)
 {
     auto tempLoc = glGetUniformLocation(GetID(), name);
     if (tempLoc == -1)
     {
       //  std::cout << "Inoccrect Unifrom Value" << std::endl;
     }
     glUniform3f(tempLoc, value.x, value.y, value.z);
 }

 void Shader::SetFloat(const char* name, float value)
 {
     auto tempLoc = glGetUniformLocation(GetID(), name);
     if (tempLoc == -1)
     {
     //    std::cout << "Inoccrect Unifrom Value" << std::endl;
     }
     glUniform1f(tempLoc, value);
 }
 void Shader::SetInt(const char* name, float value)
 {
     auto tempLoc = glGetUniformLocation(GetID(), name);
     if (tempLoc == -1)
     {
         //    std::cout << "Inoccrect Unifrom Value" << std::endl;
     }
     glUniform1i(tempLoc, value);
 }