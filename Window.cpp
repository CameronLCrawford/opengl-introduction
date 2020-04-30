#include "Window.h"
#include <iostream>

Window::Window(const unsigned int width, const unsigned int height, const char *name, glm::vec4 backgroundColour)
{
	/* Initialise projection matrix */
	const float fieldView = glm::radians(45.0f);
	const float aspectRatio = (float)1000 / (float)600;
	const float nearPlane = 0.01f;
	const float farPlane = 500.0f;
	projectionMatrix = glm::perspective(fieldView, (float)width / (float)height, nearPlane, farPlane);

	/* Load necessary libraries and set up window */
	glfwInit();

	glfwSwapInterval(1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, name, NULL, NULL);

	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);

	glClearColor(backgroundColour.x, backgroundColour.y, backgroundColour.z, backgroundColour.w);
}

Window::~Window()
{
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

void Window::draw()
{
	glfwSwapBuffers(window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update(double deltaTime)
{
	float movementSpeed = 10.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.position += movementSpeed * camera.direction;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.position -= movementSpeed * camera.direction;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.position += glm::vec3(0.0f, movementSpeed, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.position += glm::vec3(0.0f, -movementSpeed, 0.0f);
	float turnSpeed = 100.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) camera.pitch += turnSpeed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) camera.pitch -= turnSpeed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) camera.yaw += turnSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) camera.yaw -= turnSpeed;
}

glm::mat4 Window::getProjectionMatrix()
{
	camera.direction.x = glm::cos(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));
	camera.direction.y = glm::sin(glm::radians(camera.pitch));
	camera.direction.z = glm::sin(glm::radians(camera.yaw)) * glm::cos(glm::radians(camera.pitch));
	camera.direction = glm::normalize(camera.direction);
	/* 
	First crosses the direction with the vector (0, 1, 0) to obtain a vector with a direction that is either to the "left" or
	"right" of the direction vector. This is normalised and crossed with the direction vector again to get a vector that is pointing
	directly "up" from the direction vector
	*/
	glm::vec3 up = glm::normalize(glm::cross(glm::normalize(glm::cross(camera.direction, glm::vec3(0.0f, 1.0f, 0.0f))), camera.direction));
	return projectionMatrix * glm::lookAt(camera.position, camera.position + camera.direction, up);
}