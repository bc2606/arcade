/*
** EPITECH PROJECT, 2018
** IGame
** File description:
** Declaration of IGame
*/

#ifndef BOOT_IGAME_HPP
	#define BOOT_IGAME_HPP

#include <vector>
#include "interface/ICore.hpp"

class IGame : public ICore {
public:
	virtual int getScore() = 0;
	virtual void loadMap(const char *fileName) = 0;
	virtual std::vector<std::string> getMap() = 0;
	virtual bool move(Action action) = 0;
	virtual std::string getName() = 0;
	virtual int endGame() = 0;

protected:
	virtual bool move_up() = 0;
	virtual bool move_down() = 0;
	virtual bool move_right() = 0;
	virtual bool move_left() = 0;
	virtual bool playerPosFound(char p) = 0;

};


#endif /* BOOT_IGAME_HPP */
