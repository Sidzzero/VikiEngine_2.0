#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <unordered_map>
#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
private:
	static std::unordered_map<std::string, Shader> m_Shaders;
	static std::unordered_map<std::string, Texture2D> m_Textures;

public:
	static Shader GetShader(std::string a_Name);
	static Shader LoadShader(std::string name,const char* VertexShaderFileName, const char* FragmentShaderFileName);
	static Shader LoadShaderWithHardCoded(std::string name, const char* VertexShader, const char* FragmentShader);

	// loads (and generates) a texture from file
	static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
	// retrieves a stored texture
	static Texture2D GetTexture(std::string name);
	// properly de-allocates all loaded resources
	static void      Clear();


	static void Test_Texture(unsigned int& texture);

private:
	static Shader LoadShaderFromFile(const char* VertexShader, const char* FragmentShader);
	// loads a single texture from file
	static Texture2D loadTextureFromFile(const char* file, bool alpha);

};


#endif