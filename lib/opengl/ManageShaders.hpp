/*
** EPITECH PROJECT, 2018
** LoadShaders
** File description:
** Declaration of LoadShaders
*/

#ifndef ARCADE_LOADSHADERS_HPP
	#define ARCADE_LOADSHADERS_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

class ManageShaders
{
public:
	ManageShaders(const char *vertexFilePath, const char *fragmentFilePath);
	~ManageShaders();
	std::string openShaderFile(const std::string &filePath);
	void compileVertex(const std::string &shaderCode, GLuint &shaderID);
	void linkProgram(const std::string &shaderName);
	void createProgram(const std::string &shaderName);
	GLuint getProgram(const std::string &shaderName);

private:
	std::string _vertexFilePath;
	std::string _fragmentFilePath;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	GLint _result;
	int _infoLogLength;
	std::map<std::string, GLuint> _programs;
};


#endif /* ARCADE_LOADSHADERS_HPP */
