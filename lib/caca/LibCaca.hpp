/*
** EPITECH PROJECT, 2018
** libcaca
** File description:
** Declaration of libcaca
*/

#ifndef ARCADE_LIBCACA_HPP
	#define ARCADE_LIBCACA_HPP

#include <caca.h>
#include <sstream>
#include "interface/IDisplay.hpp"

class LibCaca : public IDisplay {
public:
	LibCaca();
	~LibCaca() override;
	void drawScore(int score) override;
	void drawBoard(std::vector<std::string> board) override;
	void refreshDisplay() override;
	void initScreen() override;
	void displayTitle() override;
	void displayTitle(std::string title) override;
	std::string askUsername() override;
	void multiChoiceMenu(std::vector<std::string> list, int line,
			     int index, std::string title) override;
	void playButton(int index) override;
	int getKey() override;
	Action getAction() override;
	std::string getName() override;
	void close() override;

private:
	std::string _name;
	caca_canvas_t *_canvas;
	caca_display_t *_display;
	caca_event_t _event;
	std::string _username;
};

extern "C" IDisplay *entryPoint();

#endif /* ARCADE_LIBCACA_HPP */
