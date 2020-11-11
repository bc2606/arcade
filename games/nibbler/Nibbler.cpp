/*
** EPITECH PROJECT, 2018
** Nibbler
** File description:
** Implementation of Snake
*/

#include "Nibbler.hpp"

Nibbler::Nibbler() : _score(0), _x(0), _y(0), _p('#'), _name(std::string("nibbler"))
{
	loadMap("ressources/nibbler/maps/nibbler-map.map");
	if (!playerPosFound(_p))
		std::cout << "Player not found" << std::endl;
	_snakeBodyPos.push_back(std::vector<int>());
	_snakeBodyPos[0].push_back(_x);
	_snakeBodyPos[0].push_back(_y);
}

std::vector<std::string> Nibbler::getMap()
{
	return _map;
}

std::string Nibbler::getName()
{
	return _name;
}

std::string Nibbler::getPlayer()
{
	return _player;
}

int Nibbler::getScore()
{
	return _score;
}

void Nibbler::loadMap(const char *fileName)
{
	std::ifstream fs(fileName);
	std::string line;

	if (fs.is_open()) {
		while (std::getline(fs, line))
			_map.push_back(line);
		fs.close();
	}
}

int Nibbler::endGame()
{
	for(unsigned int x = 0; x < _snakeBodyPos.size(); x++) {
		for(unsigned int y = 0; y < _snakeBodyPos.size(); y++) {
			if (x == y)
				continue;
			if (_snakeBodyPos[x][0] == _snakeBodyPos[y][0]
				&& _snakeBodyPos[x][1] == _snakeBodyPos[y][1])
				return 1;
		}
	}
	return 0;
}

void Nibbler::eat()
{
	if (_direction == MOVE_UP)
		_map[_y - 1][_x] = ' ';
	if (_direction == MOVE_DOWN)
		_map[_y + 1][_x] = ' ';
	if (_direction == MOVE_RIGHT)
		_map[_y][_x + 1] = ' ';
	if (_direction == MOVE_LEFT)
		_map[_y][_x - 1] = ' ';
	popBonus();
	_score += 10;
}

void Nibbler::popBonus()
{
	int randomRow = rand() % _map.size();
	int randomColumn = rand() % _map.size();

	while (_map[randomRow][randomColumn] != ' ') {
		randomRow = rand() % _map.size();
		randomColumn = rand() % _map.size();
	}
	_map[randomRow][randomColumn] = '.';
}

void Nibbler::bodyMove(std::vector<int> newHeadPos)
{
	newHeadPos.push_back(_x);
	newHeadPos.push_back(_y);
	if (_map[_y][_x] == '.')
		eat();
	else {
		_map[_snakeBodyPos[_snakeBodyPos.size() - 1][1]]
			[_snakeBodyPos[_snakeBodyPos.size() - 1][0]] = ' ';
		_snakeBodyPos.erase(_snakeBodyPos.end());
	}
	_map[_y][_x] = '#';
	_snakeBodyPos.insert(_snakeBodyPos.begin(), newHeadPos);
}

bool Nibbler::move_up()
{
	std::vector<int> newHeadPos;

	if (_y - 1 >= 0 && _map[_y][_x] == _p)
	{
		if (_map[_y - 1][_x] == '*')
			return false;
		_direction = MOVE_UP;
		_y--;
		bodyMove(newHeadPos);
	}
	else if (endGame() == 1)
		return false;
	return true;
}

bool Nibbler::move_down()
{
	std::vector<int> newHeadPos;

	if (_y + 1< (int)_map.size() && _map[_y][_x] == _p)
	{
		if (_map[_y + 1][_x] == '*')
			return false;
		_direction = MOVE_DOWN;
		_y++;
		bodyMove(newHeadPos);
	}
	else if (endGame() == 1)
		return false;
	return true;
}

bool Nibbler::move_right()
{
	std::vector<int> newHeadPos;

	if (_x + 1 < (int)_map[_y].size() && _map[_y][_x] == _p)
	{
		if (_map[_y][_x + 1] == '*')
			return false;
		_direction = MOVE_RIGHT;
		_x++;
		bodyMove(newHeadPos);
	}
	else if (endGame() == 1)
		return false;
	return true;
}

bool Nibbler::move_left()
{
	std::vector<int> newHeadPos;

	if (_x - 1 >= 0 && _map[_y][_x] == _p)
	{
		if (_map[_y][_x - 1] == '*')
			return false;
		_direction = MOVE_LEFT;
		_x--;
		bodyMove(newHeadPos);
	}
	else if (endGame() == 1)
		return false;
	return true;
}

bool Nibbler::move(ICore::Action action)
{
	if (action == MOVE_UP && _direction != MOVE_DOWN)
		_direction = MOVE_UP;
	if (action == MOVE_DOWN && _direction != MOVE_UP)
		_direction = MOVE_DOWN;
	if (action == MOVE_LEFT && _direction != MOVE_RIGHT)
		_direction = MOVE_LEFT;
	if (action == MOVE_RIGHT && _direction != MOVE_LEFT)
		_direction = MOVE_RIGHT;
	switch (_direction)
	{
	case MOVE_UP:
		usleep(200000);
		return move_up();
	case MOVE_DOWN:
		usleep(200000);
		return move_down();
	case MOVE_RIGHT:
		usleep(200000);
		return move_right();
	case MOVE_LEFT:
		usleep(200000);
		return move_left();
	default:
		return true;
	}
}

bool Nibbler::playerPosFound(char p)
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

extern "C" IGame *entryPoint()
{
	return new Nibbler();
}
