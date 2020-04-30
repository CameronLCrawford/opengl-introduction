#include "Shader.h"
#include "Window.h"
#include "Model.h"

#include <iostream>

#include <glm/glm.hpp>

int main()
{
	/* Initialise window */
	const unsigned int windowWidth = 1000;
	const unsigned int windowHeight = 600;
	Window window(windowWidth, windowHeight, "OpenGL Testing", glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	
	glm::vec3 lightPosition(1.2f, 1.0f, 10.0f);
	glm::vec3 lightColour(1.0f, 1.0f, 1.0f);
	
	/* Initialise shader */
	Shader shader("vertexshader.txt", "fragmentshader.txt");
	shader.setVectorUniform(3, "lightPosition", lightPosition);
	shader.setVectorUniform(3, "lightColour", lightColour);

	/* Create models present in scene */
	Model teapot("teapot.obj", glm::vec3(0.2f, 0.4f, 0.8f));

	Model cottage("cottage_obj.obj", glm::vec3(1.0f, 0.4f, 0.2f));
	cottage.move(glm::vec3(10.0f, 0.0f, 0.0f));

	Model trappedSuzanne("monkey_cube.obj", glm::vec3(0.5f, 0.4f, 0.8f));
	trappedSuzanne.move(glm::vec3(1.0f, 20.0f, 0.0f));

	while (window.isOpen())
	{
		window.clear();

		double deltaTime = glfwGetTime();
		glfwSetTime(0.0);

		std::cout << "Framerate: " << 1.0f / (float)deltaTime << '\n';

		window.update(deltaTime);

		glm::mat4 projectionMatrix = window.getProjectionMatrix();

		teapot.rotate(10.0f * (float)deltaTime, glm::vec3(0.3, 0.52, 0.2));

		teapot.draw(shader, projectionMatrix);
		trappedSuzanne.draw(shader, projectionMatrix);
		cottage.draw(shader, projectionMatrix);

		window.draw();
		glfwPollEvents();
	}
	return 0;
}