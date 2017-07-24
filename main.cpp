#include <GL/glew.h>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "itkTypes.h"
#include "misc.h"
#include <memory>
#include <vector>
#include "shaderUtils.h"
#include <map>
#include "rendering3d.h"
const std::string imagePath = GetExecutablePath();

int main(void)
{
	ImageLoaderType::Pointer imageLoader = ImageLoaderType::New();
	imageLoader->SetFileName(imagePath + "phantom.png");
	imageLoader->Update();
	ImageType::Pointer originalImage = imageLoader->GetOutput();

	GLFWwindow* window;
	//Seta o callback de erro.
	glfwSetErrorCallback([](int error, const char* description){
		std::cerr << "Error " << error << " : " << description << std::endl;
	});
	//Se falhou em iniciar, morre
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	window = glfwCreateWindow(1280, 720, "Hello GLFW", NULL, NULL);//A criação da janela é aqui
	if (!window)
	{
		//Se falhou em criar a janela, morre.
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Seta o callback de tecla;
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	});
	glfwMakeContextCurrent(window);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
	}
	glfwSwapInterval(1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";
	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
		"}";
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	
	while (!glfwWindowShouldClose(window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(window);
	}
	//Fim do loop principal
	//Limpa tudo e morre.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}