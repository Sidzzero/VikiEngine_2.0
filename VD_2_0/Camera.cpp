#include "Camera.h"

Camera::Camera()
{
}

glm::mat4 Camera::GetViewMat()
{
	return glm::lookAt(vPosition,vPosition + vFront,vUp);
}

void Camera::updateCameraTransform()
{
	
}
