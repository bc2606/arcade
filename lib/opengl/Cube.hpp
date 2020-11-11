/*
** EPITECH PROJECT, 2018
** Cube
** File description:
** Declaration of Cube
*/

#ifndef ARCADE_CUBE_HPP
	#define ARCADE_CUBE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

class Cube
{
public:
	Cube(glm::vec3 pos, glm::vec2 size, glm::vec3 color);
	void create();
	std::vector<glm::vec3> getData();
	void colorize();
	std::vector<glm::vec3> getColors();

private:
	glm::vec3 _pos;
	glm::vec2 _size;
	glm::vec3 _color;
	float _dsize;
	float _height;
	std::vector<glm::vec3> _data;
	std::vector<glm::vec3> _colors;
};


#endif /* ARCADE_CUBE_HPP */
