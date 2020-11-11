/*
** EPITECH PROJECT, 2018
** Pacman
** File description:
** Pacman
*/

#ifndef ARCADE_PACMAN_HPP
	#define ARCADE_PACMAN_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <chrono>
#include <utility>
#include <unistd.h>
#include "interface/IGame.hpp"
#include "interface/ICore.hpp"

class Pacman : public IGame {
public:
	Pacman();

	void loadMap(const char *fileName) override;
	void eat();
	bool move(Action action) override;
	int endGame() override;
	bool tryMove(Action action);
	std::vector<std::string> getMap() override;
	std::string getName() override;
	std::string getPlayer();
	int getScore() override;

protected:
	bool move_up() override;
	bool move_down() override;
	bool move_right() override;
	bool move_left() override;
	bool playerPosFound(char p) override;

private:
	std::vector<std::string> _map;
	std::string _player;
	int _score;
	long _currentMillis;
	std::vector<std::vector<int>> _snakePos;
	int _x;
	int _y;
	int _tailX;
	int _tailY;
	char _p;
	Action _direction;
	Action _newDirection;
	std::string _name;
};

extern "C" IGame *entryPoint();


#endif /* ARCADE_PACMAN_HPP */
