#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 cameraPosition = glm::vec3(6.0f, 4.0f, 6.0f);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 2.5f, 0.0f);
	glm::vec3 upCamera = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 controlViewMatrix;

	double currentFrame;
	float lastFrame = 0.0f;
	float deltaTime = 0.0f;

	float speed = 1.5f; // 3 units / second
	float verticalSpeed = 3.0f;
	float radius = 8.0f;

	float camX;
	float camZ;

	float angle = 0.0f;

	glm::mat4 getViewMatrix() { return controlViewMatrix; };

public:
	Camera();

	void GenerateFromInputs(GLFWwindow* window);

	~Camera();
};

