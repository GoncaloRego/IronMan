#include "Camera.h"

void Camera::GenerateFromInputs(GLFWwindow * window)
{
	currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition.y += verticalSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition.y -= verticalSpeed * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		angle -= speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		angle += speed * deltaTime;

	cameraPosition.x = sin(angle) * radius;
	cameraPosition.z = cos(angle) * radius;

	if (cameraPosition.y < 0.0f) cameraPosition.y = 0.0f;
	else if (cameraPosition.y > 7.0f) cameraPosition.y = 7.0f;

	controlViewMatrix = glm::lookAt(cameraPosition, cameraTarget, upCamera);
}
