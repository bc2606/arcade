/*
** EPITECH PROJECT, 2018
** Pacman
** File description:
** Implementation of Snake
*/

#include "Pacman.hpp"

Pacman::Pacman() : _score(0), _x(0), _y(0), _p('#'), _name(std::string("pacman"))
{
	loadMap("ressources/pacman/maps/pacman-map.map");
	if (!playerPosFound(_p))
		std::cout << "Player not found" << std::endl;
	_newDirection = NOTHING;
}

int Pacman::getScore()
{
	return _score;
}

void Pacman::loadMap(const char *fileName)
{
	std::ifstream fs(fileName);
	std::string line;

	if (fs.is_open())
	{
		while (std::getline(fs, line))
			_map.push_back(line);
		fs.close();
	}
}

int Pacman::endGame()
{
	int pacgum = 0;

	for (std::string str : _map) {
		for (char c : str) {
			if (c == '.')
				pacgum++;
		}
	}
	if (pacgum == 0) {
		return 0;
}
	return 1;
}

std::vector<std::string> Pacman::getMap()
{
	return _map;
}

std::string Pacman::getPlayer()
{
	return _player;
}

void Pacman::eat()
{
	if (_map[_y][_x] == '.')
	{
		_map[_y][_x] = ' ';
		_score += 10;
	}
}

bool Pacman::tryMove(Action action)
{
	if (action == MOVE_UP && _map[_y - 1][_x] == '*') {
		_newDirection = action;
		return false;
	}
	if (action == MOVE_DOWN && _map[_y + 1][_x] == '*') {
		_newDirection = action;
		return false;
	}
	if (action == MOVE_RIGHT && _map[_y][_x + 1] == '*') {
		_newDirection = action;
		return false;
	}
	if (action == MOVE_LEFT && _map[_y][_x - 1] == '*') {
		_newDirection = action;
		return false;
	}
	else
		return true;
}

bool Pacman::move_up()
{
	if (_y - 1 >= 0 && _map[_y][_x] == _p &&
	    _map[_y - 1][_x] != '*')
	{
		_direction = MOVE_UP;
		std::swap(_map[_y][_x], _map[_y - 1][_x]);
		eat();
		_y--;
	}
	if (endGame() == 0)
			return false;
	return true;
}

bool Pacman::move_down()
{
	if (_y + 1 < (int)_map.size() && _map[_y][_x] == _p &&
	    _map[_y + 1][_x] != '*')
	{
		_direction = MOVE_DOWN;
		std::swap(_map[_y][_x], _map[_y + 1][_x]);
		eat();
		_y++;
	}
	if (endGame() == 0)
			return false;
	return true;
}

bool Pacman::move_right()
{
	if (_x + 1 > (int)_map[0].size() - 1 && _map[_y][_x - _map[0].size() - 1] != '*') {
		_direction = MOVE_RIGHT;
		_map[_y][0] = ' ';
		_score += 10;
		std::swap(_map[_y][_x], _map[_y][0]);
		_x -= (int)_map[0].size() - 1;
		eat();
		return true;
	}
	if (_x + 1 < (int)_map[_y].size() && _map[_y][_x] == _p &&
	    _map[_y][_x + 1] != '*')
	{
		_direction = MOVE_RIGHT;
		std::swap(_map[_y][_x], _map[_y][_x + 1]);
		eat();
		_x++;
	}
	if (endGame() == 0)
			return false;
	return true;
}

bool Pacman::move_left()
{
	if (_x - 1 < 0 && _map[_y][_x + _map[0].size() - 1] != '*') {
		_direction = MOVE_LEFT;
		_map[_y][_map[0].size() - 1] = ' ';
		_score += 10;
		std::swap(_map[_y][_x], _map[_y][_x + (int)_map[0].size() - 1]);
		_x += (int)_map[0].size() - 1;
		eat();
		return true;
	}
	if (_x - 1 >= 0 && _map[_y][_x] == _p &&
	    _map[_y][_x - 1] != '*')
	{
		_direction = MOVE_LEFT;
		std::swap(_map[_y][_x], _map[_y][_x - 1]);
		eat();
		_x--;
	}
	if (endGame() == 0)
			return false;
	return true;
}

bool Pacman::move(ICore::Action action)
{
	if (action == MOVE_UP && tryMove(action) == true)
		_direction = MOVE_UP;
	if (action == MOVE_DOWN && tryMove(action) == true)
		_direction = MOVE_DOWN;
	if (action == MOVE_LEFT && tryMove(action) == true)
		_direction = MOVE_LEFT;
	if (action == MOVE_RIGHT && tryMove(action) == true)
		_direction = MOVE_RIGHT;
	switch (_direction)
	{
	case MOVE_UP:
		usleep(100000);
		return move_up();
	case MOVE_DOWN:
		usleep(100000);
		return move_down();
	case MOVE_RIGHT:
		usleep(100000);
		return move_right();
	case MOVE_LEFT:
		usleep(100000);
		return move_left();
	default:
		return true;
	}
}

bool Pacman::playerPosFound(char p)
{
	for (int y = 0; y < (int)_map.size(); y++) {
		for (int x = 0; x < (int)_map[y].size(); x++) {
			if (_map[y][x] == p) {
				_x = x;
				_y = y;
				return true;
			}
		}
	}
	return false;
}

std::string Pacman::getName()
{
	return _name;
}

extern "C" IGame *entryPoint()
{
	return new Pacman();
}