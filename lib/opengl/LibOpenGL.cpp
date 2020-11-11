/*
** EPITECH PROJECT, 2018
** LibOpenGL
** File description:
** Implementation of LibOpenGL
*/

#include "LibOpenGL.hpp"

LibOpenGL::LibOpenGL() : _name("OpenGL")
{}

LibOpenGL::~LibOpenGL()
{
	close();
}

void LibOpenGL::drawScore(int score)
{
	(void)score;
}

void LibOpenGL::drawBoard(std::vector<std::string> board)
{
	int nbr = 0;
	std::vector<Cube *> cubes;
	std::vector<glm::vec3> map;
	std::vector<glm::vec3> colors;
	std::vector<glm::vec3> tmp;
	glm::vec2 size;
	glm::vec3 color;

	for (int z = 0; z < (int)board.size(); z++) {
		for (int x = 0; x < (int)board[z].size(); x++) {
			if (board[z][x] != ' ') {
				switch (board[z][x]) {
					case '*':
						size = glm::vec2(1, 0.5);
						color = glm::vec3(1, 1, 1);
						break;
					case '#':
						size = glm::vec2(1, 1);
						color = glm::vec3(0, 1, 0);
						break;
					case '.':
						size = glm::vec2(0.2, 1);
						color = glm::vec3(1, 1, 0);
						break;
					default:
						break;
				}
				cubes.push_back(new Cube(glm::vec3(x, 0, z),
							 size, color));
				cubes[nbr]->create();
				tmp = cubes[nbr]->getData();
				map.insert(map.end(), tmp.begin(), tmp.end());
				cubes[nbr]->colorize();
				tmp = cubes[nbr++]->getColors();
				colors.insert(colors.end(), tmp.begin(), tmp.end());
			}
		}
	}

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) * 36) * cubes.size(),
		     &map[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) * 36) * cubes.size(),
		     &colors[0], GL_STATIC_DRAW);

	glUseProgram(_programID);
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &_mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glDrawArrays(GL_TRIANGLES, 0, (12 * 3) * (int)cubes.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glfwPollEvents();
	(void)board;
}

void LibOpenGL::refreshDisplay()
{
	glfwSwapBuffers(_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LibOpenGL::initScreen()
{
	if (!glfwInit()) {
		std::cerr << "Failed to init GLFW" << std::endl;
		exit(84);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(1200, 900, "Arcade MediEvil", NULL, NULL);
	if (!_window) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(84);
	}
	glfwGetWindowSize(_window, &_width, &_height);
	glfwMakeContextCurrent(_window);
	glewExperimental = (GLboolean)true;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to init GLEW" << std::endl;
		glfwTerminate();
		exit(84);
	}
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);
	ManageShaders *shaders = new ManageShaders("ressources/shaders/vertexShader.vs",
						   "ressources/shaders/fragmentShader.fs");
	shaders->createProgram("wall");
	_programID = shaders->getProgram("wall");;
	_matrixID = glGetUniformLocation(_programID, "MVP");
	glm::mat4 projection = glm::ortho(-13.0f, 13.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(18, 10, 15),
				     glm::vec3(8, 0, 5),
				     glm::vec3(0, 1, 0));
	glm::mat4 model(1.0f);
	_mvp = projection * view * model;
}

void LibOpenGL::displayTitle()
{

}

void LibOpenGL::displayTitle(std::string title)
{
	(void)title;
}

std::string LibOpenGL::askUsername()
{
	return std::string("");
}

void LibOpenGL::multiChoiceMenu(std::vector<std::string> list, int line,
				int index, std::string title)
{
	(void)list;
	(void)line;
	(void)index;
	(void)title;
}

void LibOpenGL::playButton(int index)
{
	(void)index;
}

int LibOpenGL::getKey()
{
	if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		return 2;
	if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS)
		return 3;
	if (glfwGetKey(_window, GLFW_KEY_LEFT) == GLFW_PRESS)
		return 4;
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		return 5;
	if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS)
		return 6;
	if (glfwGetKey(_window, GLFW_KEY_ENTER) == GLFW_PRESS)
		return 7;
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
	    glfwWindowShouldClose(_window))
		return 8;
	return 0;
}

ICore::Action LibOpenGL::getAction()
{
	int key = getKey();

	switch (key) {
		case 1:
			return MOVE_UP;
		case 2:
			return MOVE_RIGHT;
		case 3:
			return MOVE_DOWN;
		case 4:
			return MOVE_LEFT;
		case 5:
			return PREV_LIB;
		case 6:
			return NEXT_LIB;
		case 7:
			return ENTER;
		case 8:
			return ESCAPE;
		default:
			return NOTHING;
	}
}

std::string LibOpenGL::getName()
{
	return _name;
}

void LibOpenGL::close()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteVertexArrays(1, &_vertexArrayID);
	glDeleteProgram(_programID);
	glfwTerminate();
}

extern "C" IDisplay *entryPoint()
{
	return new LibOpenGL();
}