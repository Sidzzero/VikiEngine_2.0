#include "ResourceManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

//Initialize
std::unordered_map<std::string, Shader> ResourceManager::m_Shaders;

Shader ResourceManager::GetShader(std::string a_Name)
{
	return m_Shaders[a_Name];
}


Shader ResourceManager::LoadShader(std::string name,const char* VertexShader, const char* FragmentShader)
{
	m_Shaders[name] = LoadShaderFromFile(VertexShader, FragmentShader);
	return m_Shaders[name];
}
Shader ResourceManager::LoadShaderWithHardCoded(std::string name, const char* VertexShader, const char* FragmentShader)
{
	Shader shader;
	shader.Compile(VertexShader, FragmentShader);
	m_Shaders[name] = shader;
	return m_Shaders[name];
	
}
Shader ResourceManager::LoadShaderFromFile(const char* VertexShader, const char* FragmentShader)
{
	std::string vertexCode;
	std::string fragmentCode;
	
	try
	{
		std::ifstream vertexShaderFile(VertexShader);
		std::ifstream fragmentShaderFile(VertexShader);
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexShaderFile.rdbuf();
		fragmentStream << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

	}
	catch (std::exception exp)
	{
		std::cout << "ERROR: SHADER ERROR: FAiled to READ:" << exp.what();
	
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. now create shader object from source code
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode);
	return shader;

}

