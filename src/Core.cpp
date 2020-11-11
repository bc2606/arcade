/*
** EPITECH PROJECT, 2018
** Core
** File description:
** Implementation of Core
*/

#include "Core.hpp"

Core::Core(const char *libPath) :
	_libPath(std::string(libPath)),
	_displayHandler(DLLoader<IDisplay>(_libPath)),
	_gameHandler(DLLoader<IGame>("games/lib_arcade_nibbler.so"))
{
	_display = _displayHandler.getInstance();
	_game = _gameHandler.getInstance();
	_libVector = listDynLib("lib/");
	_gameVector = listDynLib("games/");
	_libNbr = findVectorPos(_libVector, _libPath);
}

Core::~Core() {
	_displayHandler.close();
	_gameHandler.close();
}

void Core::saveHighScore()
{
	std::string path("ressources/" + _game->getName() + "/Highscore.txt");
	std::fstream record;

	record.open(path.c_str(), std::fstream::in |
				  std::fstream::out |
				  std::fstream::app);
	if (!record.is_open()) {
		record.open(path.c_str(), std::fstream::in |
					  std::fstream::out |
					  std::fstream::trunc);
	}
	record << _userName << "\t" << _game->getScore() << std::endl;
	record.close();
}

void Core::highScoreVector()
{
	std::string path("ressources/" + _game->getName() + "/Highscore.txt");
	std::fstream score;
	std::string line;

	score.open(path.c_str(), std::fstream::in | std::fstream::out);
	if (score.is_open()) {
		while (std::getline(score, line))
			_highScore.push_back(line);
		score.close();
	}
}

void Core::menu()
{
	Action action;
	int index = 0;
	std::vector<int> indexLine;

	_display->initScreen();
	indexLine.reserve(2);
	for (int i = 0; i < 2; i++)
		indexLine.push_back(0);
	_userName = _display->askUsername();
	while (index < 3) {
		_display->displayTitle(_userName);
		_display->multiChoiceMenu(_libVector, indexLine[0],
					  0, "Libs");
		_display->multiChoiceMenu(_gameVector, indexLine[1],
					  1, "Games");
		action = _display->getAction();
		if (index == 0) {
			indexLine[0] = moveLine(action, indexLine[0],
						(int) _libVector.size());
		} else if (index == 1) {
			indexLine[1] = moveLine(action, indexLine[1],
						(int) _gameVector.size());
		}
		if (index > 1)
			_display->multiChoiceMenu(_highScore, -1, 2, "Scores");
		if (action == ENTER) {
			switch (index) {
				case 0:
					_displayHandler = DLLoader<IDisplay>(_libVector[indexLine[0]]);
					_displayTmp = _displayHandler.getInstance();
					break;
				case 1:
					_gameHandler = DLLoader<IGame>(_gameVector[indexLine[1]]);
					_game = _gameHandler.getInstance();
					highScoreVector();
					break;
				default: break;
			}
			index++;
		}
		_display->playButton(index);
		_display->refreshDisplay();
		changeLib(action);
	}
	_display->close();
}

void Core::game()
{
	Action action = NOTHING;
	std::vector<std::string> map;

	_display = _displayTmp;
	_display->initScreen();
	while (action != ESCAPE) {
		map = _game->getMap();
		_display->displayTitle(_userName);
		_display->drawScore(_game->getScore());
		_display->drawBoard(map);
		action = _display->getAction();
		if (!_game->move(action)) {
			break;
		}
		_display->refreshDisplay();
		changeLib(action);
	}
	saveHighScore();
}

std::vector<std::string> Core::listDynLib(const char *directoryPath)
{
	std::vector<std::string> list;
	DIR *directory;
	struct dirent *file = nullptr;

	if ((directory = opendir(directoryPath)) == nullptr) {
		std::cout << "Error opening directory" << std::endl;
	}
	while ((file = readdir(directory)))
		if (file->d_type == DT_REG &&
		    isDynLib(file->d_name, std::string(".so")))
			list.push_back(std::string(directoryPath) +
				       file->d_name);
	closedir(directory);
	return list;
}

bool Core::isDynLib(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(),
			    suffix.size(), suffix) == 0;
}

void Core::changeLib(ICore::Action action)
{
	switch (action) {
		case PREV_LIB:
			_libNbr--;
			break;
		case NEXT_LIB:
			_libNbr++;
			break;
		default: return;
	}
	_libNbr = _libNbr < 0 ? (int)_libVector.size() - 1 : _libNbr;
	_libNbr = _libNbr < (int)_libVector.size() ? _libNbr : 0;
	_display->close();
	_displayHandler = DLLoader<IDisplay>(_libVector[_libNbr]);
	_display = _displayHandler.getInstance();
	_display->initScreen();
}

int Core::findVectorPos(std::vector<std::string> vector, std::string el)
{
	return (int)(std::distance(vector.begin(), std::find(vector.begin(),
							     vector.end(),
							     el)));
}

std::string Core::removeBegin(std::string str, std::string sub)
{
	std::string tmp(str);
	std::string::size_type i = tmp.find(sub);

	if (i != std::string::npos)
		tmp.erase(i, sub.size());
	return tmp;
}

int Core::moveLine(ICore::Action action, int index, int max)
{
	int newIndex = index;

	switch (action) {
		case MOVE_UP:
			if (newIndex - 1 >= 0)
				newIndex--;
			break;
		case MOVE_DOWN:
			if (newIndex + 1 < max)
				newIndex++;
			break;
		default: break;
	}
	return newIndex;
}
