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
	std::shared_ptr<Object3d> resource = nullptr;
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
	glfwSwapInterval(1);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//Loop principal é aqui
	bool isInitialized = false;
	std::shared_ptr<Object3d> myObject = nullptr;
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);		
		if (!isInitialized)
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
			// start GLEW extension handler
			glewExperimental = GL_FALSE;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				/* Problem: glewInit failed, something is seriously wrong. */
				printf("Error: %s\n", glewGetErrorString(err));
			}

			myObject = std::make_shared<Object3d>();
			//myObject->Init(originalImage);
			isInitialized = true;
		}
		else
		{
			myObject->Render();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	//Fim do loop principal
	//Limpa tudo e morre.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}