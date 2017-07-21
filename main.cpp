#include <GL/glew.h>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "itkTypes.h"

// #define LOG_FORMATS

static void error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << " : " << description << std::endl;
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}


std::ostream& operator<<(std::ostream& str, const GLFWvidmode& vidmode)
{
	str << "\n{ // GLFWvidmode \n";
	str << "\twidth = " << vidmode.width << '\n';
	str << "\theight = " << vidmode.height << '\n';
	str << "\tredBits = " << vidmode.redBits << '\n';
	str << "\tgreenBits = " << vidmode.greenBits << '\n';
	str << "\tblueBits = " << vidmode.blueBits << '\n';
	str << "\trefreshRate = " << vidmode.refreshRate << '\n';
	str << "\n}\n" << std::endl;

	return str;
}


int main(void)
{
	Teste::Pointer t = Teste::New();


	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	window = glfwCreateWindow(1280, 720, "Hello GLFW", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
#ifdef LOG_FORMATS

	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	for (int i = 0; i < count; i++)
	{
		std::clog << modes[i] << std::endl;
	}

#endif

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}