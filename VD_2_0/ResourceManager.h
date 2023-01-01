#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <unordered_map>
#include "Shader.h"
class ResourceManager
{
private:
	static std::unordered_map<std::string, Shader> m_Shaders;

public:
	static Shader GetShader(std::string a_Name);
	static Shader LoadShader(std::string name,const char* VertexShaderFileName, const char* FragmentShaderFileName);
	static Shader LoadShaderWithHardCoded(std::string name, const char* VertexShader, const char* FragmentShader);


private:
	static Shader LoadShaderFromFile(const char* VertexShader, const char* FragmentShader);

};


#endif