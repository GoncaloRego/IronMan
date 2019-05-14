#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

//Camera & Matrices


//Identity Matrix
glm::mat4 identity(1.0f);

//Model Matrix
glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f); //vector for translation
glm::mat4 translationMatrix = glm::translate(identity, translation);

float angleInDegrees = 0; //rotation in degrees
glm::vec3 rotationAxis(0, 0, 0); // axis for rotation
glm::mat4 rotationMatrix = glm::rotate(angleInDegrees, rotationAxis);

float scale = 2; //scale
glm::mat4 scaleMatrix = glm::scale(glm::vec3(scale, scale, scale));

//glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
glm::mat4 modelMatrix = glm::mat4(1.0f);


//ViewMatrix
glm::vec3 cameraPosition = glm::vec3(3, 3, 3); // Camera position in World Space
glm::vec3 lookAtPosition = glm::vec3(0, 0, 0); // Position to look at

glm::mat4 viewMatrix = glm::lookAt(cameraPosition, lookAtPosition, glm::vec3(0.0f, 1.0f, 0.0f));
//----------//


//ProjectionMatrix
float fieldOfView = 45;
float aspectRatio = 1920 / 1080;
float near = 0.1f;
float far = 100;

glm::mat4 projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, near, far);

//ModelViewProjection Matrix
glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	//GlewInit after the window creation
	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);


	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void Initialization()
{
	// Background
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	/*glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);*/
}