#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Window
{
public:
	Window(unsigned int, unsigned int, const char *, glm::vec4);
	~Window();

	bool isOpen();

	void clear();

	void draw();

	void update(double);

	glm::mat4 getProjectionMatrix();

private:
	struct Camera
	{
		glm::vec3 position = glm::vec3 (0.0f, 0.0f, -7.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
		float pitch = 0.0f;
		float yaw = 0.0f;
	} camera;

	GLFWwindow *window;
	glm::mat4 projectionMatrix;
};

