/*
** EPITECH PROJECT, 2018
** Cube
** File description:
** Implementation of Cube
*/

#include "Cube.hpp"

Cube::Cube(glm::vec3 pos, glm::vec2 size, glm::vec3 color) : _pos(pos),
							     _size(size),
							     _color(color)
{
	_dsize = _size.x / 2;
	_height = _size.x * _size.y;
}

void Cube::create()
{
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z - _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x - _dsize, _pos.y + _height, _pos.z + _dsize));
	_data.push_back(glm::vec3(_pos.x + _dsize, _pos.y, _pos.z + _dsize));
}

std::vector<glm::vec3> Cube::getData()
{
	return _data;
}

void Cube::colorize()
{
	for (int i = 0; i < 12 * 3; i++) {
		_colors.push_back(glm::vec3(_color.x, _color.y, _color.z));
	}
}

std::vector<glm::vec3> Cube::getColors()
{
	return _colors;
}
