#include "Camera.h"

Camera::Camera()
{
	vPosition = glm::vec3(0,0,-20);
	vFront = glm::vec3(0,0,1);
	vUp = glm::vec3(0, 1.0f, 0);
	vRight = glm::vec3(1.0f,0.0f,0);
}

glm::mat4 Camera::GetViewMat()
{
	return glm::lookAt(vPosition,vPosition + vFront,vUp);
}

void Camera::updateCameraTransform()
{
	
}
