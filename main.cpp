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
const std::string imagePath = GetExecutablePath();

class myResources
{
private:
	GLuint vertexBuffer, elementBuffer;
	GLuint texture;
	std::vector<GLfloat> vertexBufferData;
	std::vector<GLushort> elementBufferData;
	MyShader shader;
public:
	static GLuint makeBuffer(GLenum target, const void *bufferData, GLsizei bufferSize)
	{
		GLuint buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(target, buffer);
		glBufferData(target, bufferSize, bufferData, GL_STATIC_DRAW);
		return buffer;
	}

	static GLuint makeTexture(ImageType::Pointer imagemDaITK)
	{
		//TODO : O dado vem de uma imagem da ITK, com um float por pixel
		GLuint texture;

		void *pixels = imagemDaITK->GetBufferPointer();
		if (!pixels)
			return 0;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,           /* target, level of detail */
			GL_RED,                    /* internal format */
			imagemDaITK->GetLargestPossibleRegion().GetSize()[0],
			imagemDaITK->GetLargestPossibleRegion().GetSize()[1],
			0,           /* width, height, border */
			GL_RED, GL_FLOAT,   /* external format, type */
			pixels                      /* pixels */
			);
		return texture;
	}

	void Init(ImageType::Pointer imagemDaITK)
	{
		vertexBufferData.push_back(-1.0f); vertexBufferData.push_back(-1.0f);
		vertexBufferData.push_back( 1.0f); vertexBufferData.push_back(-1.0f);
		vertexBufferData.push_back(-1.0f); vertexBufferData.push_back( 1.0f);
		vertexBufferData.push_back( 1.0f); vertexBufferData.push_back( 1.0f);

		elementBufferData.push_back(0);
		elementBufferData.push_back(1);
		elementBufferData.push_back(2);
		elementBufferData.push_back(3);
		std::cout<<vertexBufferData.data()[0];

		vertexBuffer = makeBuffer(GL_ARRAY_BUFFER, vertexBufferData.data(), vertexBufferData.size()*sizeof(GLfloat));
		elementBuffer = makeBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferData.data(), elementBufferData.size()*sizeof(GLushort));
		texture = makeTexture(imagemDaITK);

		shader = CreateShaderProgram(imagePath + "vertexShader.glsl", imagePath + "fragmentShader.glsl");
		std::cout << endl;
	}
};

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
	window = glfwCreateWindow(1280, 720, "Hello GLFW", NULL, NULL);//A cria��o da janela � aqui
	std::shared_ptr<myResources> resource = nullptr;
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
	//Loop principal � aqui
	bool isInitialized = false;
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		std::shared_ptr<myResources> myObject = nullptr;//std::make_shared<myResources>();
		if (!isInitialized)
		{
			glfwSwapBuffers(window);
			glfwPollEvents();
			// start GLEW extension handler
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				/* Problem: glewInit failed, something is seriously wrong. */
				printf("Error: %s\n", glewGetErrorString(err));
			}

			myObject = std::make_shared<myResources>();
			myObject->Init(originalImage);
			isInitialized = true;
		}
		else
		{
			//...
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