/*
** EPITECH PROJECT, 2018
** LoadShaders
** File description:
** Implementation of LoadShaders
*/

#include "ManageShaders.hpp"

ManageShaders::ManageShaders(const char *vertexFilePath,
			 const char *fragmentFilePath) :
	_vertexFilePath(vertexFilePath), _fragmentFilePath(fragmentFilePath),
	_result(GL_FALSE), _infoLogLength(0)
{
}

ManageShaders::~ManageShaders()
{
	for (auto const &program : _programs) {
		glDetachShader(program.second, _vertexShaderID);
		glDetachShader(program.second, _fragmentShaderID);
	}
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}


std::string ManageShaders::openShaderFile(const std::string &filePath)
{
	std::string shaderCode;
	std::ifstream shaderStream(filePath.c_str(), std::ios::in);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	} else {
		std::cerr << "Cannot open " << filePath << std::endl;
		return 0;
	}
	return shaderCode;
}

void ManageShaders::compileVertex(const std::string &shaderCode, GLuint &shaderID)
{
	char const *sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &_infoLogLength);
	if (_infoLogLength > 0) {
		std::vector<char> shaderErrorMessage(_infoLogLength + 1);
		glGetShaderInfoLog(shaderID, _infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cerr << &shaderErrorMessage[0] << std::endl;
	}
}

void ManageShaders::linkProgram(const std::string &shaderName)
{
	GLuint programID;

	programID = glCreateProgram();
	glAttachShader(programID, _vertexShaderID);
	glAttachShader(programID, _fragmentShaderID);
	glLinkProgram(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &_result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &_infoLogLength);
	if (_infoLogLength > 0) {
		std::vector<char> programErrorMessage(_infoLogLength + 1);
		glGetProgramInfoLog(programID, _infoLogLength, NULL, &programErrorMessage[0]);
		std::cerr << &programErrorMessage[0] << std::endl;
	}
	_programs[shaderName] = programID;
}

void ManageShaders::createProgram(const std::string &shaderName)
{

	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	compileVertex(openShaderFile(_vertexFilePath), _vertexShaderID);
	compileVertex(openShaderFile(_fragmentFilePath), _fragmentShaderID);
	linkProgram(shaderName);
}

GLuint ManageShaders::getProgram(const std::string &shaderName)
{
	return _programs.at(shaderName);
}