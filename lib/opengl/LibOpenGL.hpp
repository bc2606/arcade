/*
** EPITECH PROJECT, 2018
** LibOpenGL
** File description:
** Declaration of LibOpenGL
*/

#ifndef ARCADE_LIBOPENGL_HPP
	#define ARCADE_LIBOPENGL_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include "interface/IDisplay.hpp"
#include "ManageShaders.hpp"
#include "Cube.hpp"

class LibOpenGL : public IDisplay {
public:
	LibOpenGL();
	~LibOpenGL() override;
	void drawScore(int score) override;
	void drawBoard(std::vector<std::string> board) override;
	void refreshDisplay() override;
	void initScreen() override;
	void displayTitle() override;
	void displayTitle(std::string title) override;
	std::string askUsername() override;
	void multiChoiceMenu(std::vector<std::string> list, int line,
			     int index, std::string title) override;
	void playButton(int index) override;
	int getKey() override;
	Action getAction() override;
	std::string getName() override;
	void close() override;

private:
	std::string _name;
	GLFWwindow *_window;
	GLuint _vertexArrayID;
	const GLfloat *_vertexBufferData;
	GLuint _vertexBuffer;
	GLuint _triVertexBuffer;
	GLuint _colorBuffer;
	GLuint _programID;
	GLuint _matrixID;
	int _width;
	int _height;
	glm::mat4 _mvp;
};

extern "C" IDisplay *entryPoint();

#endif /* ARCADE_LIBOPENGL_HPP */
