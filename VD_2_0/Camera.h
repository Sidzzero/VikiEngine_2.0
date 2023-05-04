#pragma once
#include "common.h"
class Camera
{
public:
	Camera();
	glm::mat4 GetViewMat();
private:
	void updateCameraTransform();
	glm::vec3 vPosition;
	glm::vec3 vUp;
	glm::vec3 vFront;
	glm::vec3 vRight;

	float pitch;
	float yaw;

	float mouseSentivity;
	float zoomSentivity;

};

