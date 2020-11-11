/*
** EPITECH PROJECT, 2018
** Nibbler
** File description:
** Declaration of Snake
*/

#ifndef ARCADE_SNAKE_HPP
	#define ARCADE_SNAKE_HPP

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

class Nibbler : public IGame {
public:
	Nibbler();

	void loadMap(const char *fileName) override;
	void eat();
	void popBonus();
	bool move(Action action) override;
	int endGame() override;
	void bodyMove(std::vector<int> newHeadPos);
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
	std::vector<std::vector<int>> _snakeBodyPos;
	int _x;
	int _y;
	int _tailX;
	int _tailY;
	char _p;
	Action _direction;
	std::string _name;
};

extern "C" IGame *entryPoint();


#endif /* ARCADE_SNAKE_HPP */
