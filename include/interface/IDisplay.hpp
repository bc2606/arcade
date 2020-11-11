/*
** EPITECH PROJECT, 2018
** IDisplay
** File description:
** Declaration of IDisplay
*/

#ifndef BOOT_IDISPLAY_HPP
	#define BOOT_IDISPLAY_HPP

#include <iostream>
#include <vector>
#include "interface/ICore.hpp"

class IDisplay : public ICore {
public:
	virtual ~IDisplay() = 0;
	virtual void drawScore(int score) = 0;
	virtual void drawBoard(std::vector<std::string> board) = 0;
	virtual void refreshDisplay() = 0;
	virtual void initScreen() = 0;
	virtual void displayTitle() = 0;
	virtual void displayTitle(std::string title) = 0;
	virtual std::string askUsername() = 0;
	virtual void multiChoiceMenu(std::vector<std::string> list, int line,
				     int index, std::string title) = 0;
	virtual void playButton(int index) = 0;
	virtual int getKey() = 0;
	virtual Action getAction() = 0;
	virtual std::string getName() = 0;
	virtual void close() = 0;
};


#endif /* BOOT_IDISPLAY_HPP */
