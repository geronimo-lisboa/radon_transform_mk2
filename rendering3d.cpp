#include "rendering3d.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;
std::string Shader::ReadShaderFile(std::string path)
{
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(path.c_str(), std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
		throw std::exception("arquivo não foi aberto");
	}
	return VertexShaderCode;
}

void Shader::introspectProgram(GLuint programId, map<string, GLuint>& attributes, map<string, GLuint>& uniforms)
{
	GLint numberOfAttributes, largestAttributeName;
	glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTES, &numberOfAttributes);
	glGetProgramiv(programId, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &largestAttributeName);
	//para cada atributo, pegar as propriedades e guardar.
	for (GLint i = 0; i < numberOfAttributes; i++)
	{
		char* nameBuffer = new char[largestAttributeName];
		GLsizei length;
		GLint size;
		GLenum type;
		//Pega, entre outras coisas, o nome do atributo.
		glGetActiveAttrib(programId, i, largestAttributeName, &length, &size, &type, nameBuffer);
		GLint attribLocation = glGetAttribLocation(programId, nameBuffer);
		std::string _name(nameBuffer);
		attributes.insert(std::make_pair(_name, attribLocation));
	}
	//Agora pra uniforms
	GLint numberOfUniforms, largesUniformName;
	glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
	glGetProgramiv(programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &largesUniformName);
	//para cada atributo, pegar as propriedades e guardar.
	for (GLint i = 0; i < numberOfUniforms; i++)
	{
		char* buffer = new char[largesUniformName];
		GLsizei length;
		GLint size;
		GLenum type;
		glGetActiveUniform(programId, i, largesUniformName, &length,
			&size, &type, buffer);
		GLint unifLoc = glGetUniformLocation(programId, buffer);
		std::string _name(buffer);
		uniforms.insert(std::make_pair(_name, unifLoc));
	}
}

string Shader::GetShaderInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
	GLint log_length;
	char *log;
	glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
	log = static_cast<char*>(malloc(log_length));
	glGet__InfoLog(object, log_length, nullptr, log);
	return log;
}

GLuint Shader::MakeShader(GLenum type, std::string source)
{
	GLint length[] = { source.length() };
	const GLchar *srcLn = source.c_str();
	GLuint shader;
	GLint shader_ok;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &srcLn, length);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
	if (!shader_ok)
	{
		string _probl = GetShaderInfoLog(shader, glGetShaderiv, glGetShaderInfoLog);
		glDeleteShader(shader);
		throw std::runtime_error(_probl.c_str());
	}
	else
	{
		return shader;
	}
}

GLuint Shader::MakeProgram(GLuint vertex_shader, GLuint fragment_shader)
{
	GLint program_ok;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
	if (!program_ok) {
		string _probl = GetShaderInfoLog(program, glGetProgramiv, glGetProgramInfoLog);
		glDeleteProgram(program);
		throw std::runtime_error(_probl.c_str());
	}
	return program;
}

Shader::Shader(string vsPath, string fsPath)
{
	std::string vsSrc = ReadShaderFile(vsPath);
	vsId = MakeShader(GL_VERTEX_SHADER, vsSrc);
	std::string fsSrc = ReadShaderFile(fsPath);
	fsId = MakeShader(GL_FRAGMENT_SHADER, fsSrc);
	programId = MakeProgram(vsId, fsId);
	introspectProgram(programId, attributes, uniforms);
}

Shader::~Shader()
{
	glDeleteShader(vsId);
	glDeleteShader(fsId);
	glDeleteShader(programId);
}

GLuint Shader::GetUniform(string name)
{
	return uniforms.at(name);
}

GLuint Shader::GetAttribute(string name)
{
	return attributes.at(name);
}

GLuint Shader::GetProgramId()
{
	return programId;
}

void Shader::UseProgram()
{
	glUseProgram(this->programId);
}

Object3d::Object3d() :shader("C:\\programacao\\radon_transform_mk2_build\\Debug\\vertexShader.glsl", 
	"C:\\programacao\\radon_transform_mk2_build\\Debug\\fragmentShader.glsl")
{
	vertexes.push_back(-1.0f); vertexes.push_back(-1.0f); vertexes.push_back(0.0f);
	vertexes.push_back(1.0f); vertexes.push_back(-1.0f); vertexes.push_back(0.0f);
	vertexes.push_back(0.0f); vertexes.push_back(1.0f); vertexes.push_back(0.0f);
	size_t sz = vertexes.size();
	std::cout << sz << std::endl;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertexes.size()*sizeof(float), vertexes.data(), GL_STATIC_DRAW);

	GLint size = 0;
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size); 
	std::cout << "Buffer na gpu = " << size << std::endl;
}

void teste_opengl()
{
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << "erro de opengl em algum lugar";
		throw err;
	}
}
void Object3d::Render()
{
	teste_opengl();
	shader.UseProgram();
	teste_opengl();
	//glBindVertexArray(vao);
	teste_opengl();
	glEnableVertexAttribArray(0);
	teste_opengl();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	teste_opengl();
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	teste_opengl();
	glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
	teste_opengl();
	//glDisableVertexAttribArray(0);
}
