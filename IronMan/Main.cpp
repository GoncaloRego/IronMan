#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>

#include "Camera.h"
#include "ObjLoader.h"

unsigned int programID;

unsigned int vertexBuffer;
unsigned int uvBuffer;
unsigned int normalBuffer;
unsigned int elementBuffer;

unsigned int vertexArrayID;

unsigned int matrixID;
unsigned int viewMatrixID;
unsigned int modelMatrixID;

std::vector< glm::vec3 > vertices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals;

std::vector<unsigned short> indices;
std::vector<glm::vec3> indexed_vertices;
std::vector<glm::vec2> indexed_uvs;
std::vector<glm::vec3> indexed_normals;

ObjLoader objLoader;

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

	//Initialization();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.0f,  0.5f);
		glVertex2f( 0.5f, -0.5f);
		glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	//Clean VBO and Shader
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &normalBuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vertexArrayID);

    glfwTerminate();
    return 0;
}

void Initialization(void)
{
	// Background
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	// Read our .obj file
	bool obj = objLoader.loadOBJ("Model/Iron_Man.obj", vertices, uvs, normals);

	// Create and compile our GLSL program from the shaders
	//programID = LoadShaders("shaders/triangles.vert", "shaders/triangles.frag");

	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "V");
	modelMatrixID = glGetUniformLocation(programID, "M");
}