#ifndef  VD_CLIENT_H
#define VD_CLIENT_H

#include "Client.h"
#include "common.h"
#include "ResourceManager.h"
#include <iostream>
#include "Camera.h"
class VD_Client :
    public Client
{
public:
	 void Init(GLFWwindow* a_window) override;

	 void Input(float dt) override;
	 void Update(float dt) override;
	 void Render() override;

	 //TODO: MAke a scene manager
	 Mesh square;
	 Buffer triangleRenderer;
	 unsigned int shaderProgram;

	 Mesh Cube;
	 Buffer cubeRenderer;

	 Camera cam;
	 float xLast = 300, yLast = 300;

	 Mesh LightCube;
	 Buffer lightRenderer;
	 glm::vec3 lightPosition;
private:

	
	
};
#endif
