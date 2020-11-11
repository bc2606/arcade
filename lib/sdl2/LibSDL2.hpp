/*
** EPITECH PROJECT, 2018
** LibSDL2
** File description:
** Declaration of LibSDL2
*/

#ifndef ARCADE_LIBSDL2_HPP
	#define ARCADE_LIBSDL2_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <sstream>
#include "interface/IDisplay.hpp"

class LibSDL2 : public IDisplay {
public:
	LibSDL2();
	~LibSDL2() override;
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
	void loadTexture();
	std::string getName() override;
	void close() override;

private:
	SDL_Rect _winSize{};
	std::string _name;
	SDL_Window *_window;
	SDL_Event _event;
	SDL_Renderer *_windowRenderer;
	std::map<std::string, SDL_Texture *> _textureMap;
	SDL_Surface *_loadSurface;
	TTF_Font *_fontArcade;
	TTF_Font *_fontRoboto;
	SDL_Color _whiteC;
	SDL_Color _yellowC;
};

extern "C" IDisplay *entryPoint();

#endif /* ARCADE_LIBSDL2_HPP */
