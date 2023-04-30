#ifndef SHADER_H
#define SHADER_H
#include "common.h"
#include <iostream>
#include <string>
class Shader
{
public:
	Shader();
	void Use();
	void Compile(const char* vertexSource, const char* fragmentSource);
	int GetID();
private:
	void checkCompileErrors(unsigned int object, std::string type);
	unsigned int ID;
	//Functions for settings uniforms...

};

#endif

