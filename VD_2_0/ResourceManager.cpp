#include "ResourceManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

//Initialize
std::unordered_map<std::string, Shader> ResourceManager::m_Shaders;
std::unordered_map<std::string, Texture2D> ResourceManager::m_Textures;

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

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
	m_Textures[name] = loadTextureFromFile(file, alpha);
	return m_Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	return m_Textures[name];
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

void ResourceManager::Clear()
{
	// (properly) delete all shaders	
	for (auto iter : m_Shaders)
		glDeleteProgram(iter.second.ID);
	// (properly) delete all textures
	for (auto iter : m_Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	// create texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	// now generate texture
	texture.Generate(width, height, data);
	// and finally free image data
	stbi_image_free(data);
	return texture;
}
