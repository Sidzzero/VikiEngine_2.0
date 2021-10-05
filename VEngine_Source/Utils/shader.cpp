//
//  shader.cpp
//  VEngine_Source
//
//  Created by Srikanth_Siddhu on 05/10/21.
//

#include "shader.hpp"
shader::shader(const char *vertSource , const char *fragSource)
{
    
    //1. Load file contents
    std::string vertexCode;
    std::string fragmentCode;
    
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //Enables these objects to theow expections...
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertSource);
        fShaderFile.open(fragSource);
        
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::IN SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
       std:: cerr << "Error code: " << strerror(errno)<<std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    
    // 2. compile programs
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
       
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };
    
        // Frag Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        // print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        };
    //3 . Shader program
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
      
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}
void shader::Use()
{
    glUseProgram(ID);
}
void shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void shader::setFloat4(const std::string &name , float x ,float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID,name.c_str()), x,y,z,w );
}
