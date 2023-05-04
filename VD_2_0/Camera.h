#pragma once
#include "common.h"
class Camera
{
public:
	Camera();
	glm::mat4 GetViewMat();
	glm::vec3 vPosition;
	glm::vec3 vUp;
	glm::vec3 vFront;
	glm::vec3 vRight;
	float pitch;
	float yaw;

	float mouseSentivity = 0.5f;
	float KeyboardSentivity = 0.5f;
	float zoomSentivity = 0.5f;


private:
	void updateCameraTransform();


	

};

