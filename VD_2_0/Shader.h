#ifndef SHADER_H
#define SHADER_H
#include "common.h"
#include <iostream>
#include <string>
class Shader
{
public:
	Shader();
	unsigned int ID;
	void Use();
	void Compile(const char* vertexSource, const char* fragmentSource);
private:
	void checkCompileErrors(unsigned int object, std::string type);

	//Functions for settings uniforms...

};

#endif

