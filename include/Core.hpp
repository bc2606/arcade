/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Declaration of Core
*/

#ifndef ARCADE_CORE_HPP
	#define ARCADE_CORE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <dirent.h>
#include "DLLoader.hpp"
#include "interface/IDisplay.hpp"
#include "interface/IGame.hpp"

class Core : public ICore {
public:
	Core(const char *libPath);
	~Core();
	void menu();
	void game();
	std::vector<std::string> listDynLib(const char *directoryPath);
	bool isDynLib(const std::string &str, const std::string &suffix);
	void saveHighScore();
	void changeLib(Action action);
	int findVectorPos(std::vector<std::string> vector, std::string el);
	std::string removeBegin(std::string str, std::string sub);
	int moveLine(Action action, int index, int max);
	void highScoreVector();

private:
	std::string _userName;
	std::string _libPath;
	std::vector<std::string> _map;
	DLLoader<IDisplay> _displayHandler;
	IDisplay *_display;
	IDisplay *_displayTmp;
	DLLoader<IGame> _gameHandler;
	IGame *_game;
	std::vector<std::string> _libVector;
	int _libNbr;
	std::vector<std::string> _gameVector;
	int _gameNbr;
	std::vector<std::string> _highScore;
};


#endif /* ARCADE_CORE_HPP */
