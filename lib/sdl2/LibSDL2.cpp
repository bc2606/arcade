/*
** EPITECH PROJECT, 2018
** LibSDL2
** File description:
** Implementation of LibSDL2
*/

#include "LibSDL2.hpp"

LibSDL2::LibSDL2() : _name("SDL2")
{
	_whiteC = {255, 255, 255, 255};
	_yellowC = {255, 255, 0, 255};
}

LibSDL2::~LibSDL2()
{
	close();
}

void LibSDL2::drawScore(int score)
{
	std::stringstream ss;
	ss << score;
	std::string scr = ss.str();
	SDL_Rect scoreZone = {_winSize.w - 100, 25, 50, 20};

	_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, "Score", _whiteC);
	_textureMap["scoreT"] = SDL_CreateTextureFromSurface(_windowRenderer,
							    _loadSurface);
	SDL_FreeSurface(_loadSurface);
	SDL_RenderCopy(_windowRenderer, _textureMap["scoreT"],
		       NULL, &scoreZone);
	_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, scr.c_str(), _whiteC);
	_textureMap["score"] = SDL_CreateTextureFromSurface(_windowRenderer,
							     _loadSurface);
	scoreZone = {_winSize.w - 100, 40, _loadSurface->w, _loadSurface->h};
	SDL_FreeSurface(_loadSurface);
	SDL_RenderCopy(_windowRenderer, _textureMap["score"],
		       NULL, &scoreZone);
}

void LibSDL2::drawBoard(std::vector<std::string> board)
{
	int startX = SDL_GetWindowSurface(_window)->w / 2;
	int startY = SDL_GetWindowSurface(_window)->h / 2;
	SDL_Rect block{};
	SDL_Rect pos{};

	startX -= (board[0].size() * 20) / 2;
	startY -= (board.size() * 20) / 2;
	for (int y = 0; y < (int)board.size(); y++) {
		for (int x = 0; x < (int)board[y].size(); x++) {
			pos = {96, 0, 16, 16};
			block = {startX + (20 * x), startY + (20 * y), 20, 20};
			switch (board[y][x]) {
				case '*':
					SDL_RenderCopy(_windowRenderer,
						       _textureMap["assets"],
						       &pos, &block);
					break;
				case '.':
					pos.x = 112;
					SDL_RenderCopy(_windowRenderer,
						       _textureMap["assets"],
						       &pos, &block);
					break;
				case '#':
					pos.y = 16;
					SDL_RenderCopy(_windowRenderer,
						       _textureMap["assets"],
						       &pos, &block);
					break;
				default: break;
			}
		}
	}
}

void LibSDL2::refreshDisplay()
{
	SDL_RenderPresent(_windowRenderer);
	SDL_RenderClear(_windowRenderer);
}

void LibSDL2::initScreen()
{
	Uint32 rFlag = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
		SDL_Quit();
		TTF_Quit();
		exit(84);
	}
	_window = SDL_CreateWindow("Arcade de Sir Daniel Fortesque",
				   SDL_WINDOWPOS_CENTERED,
				   SDL_WINDOWPOS_CENTERED,
				   1180, 940,
				   SDL_WINDOW_SHOWN);
	if (_window == 0) {
		SDL_Quit();
		TTF_Quit();
		exit(84);
	}
	_windowRenderer = SDL_CreateRenderer(_window, -1, rFlag);
	_fontArcade = TTF_OpenFont("ressources/font/arcade.ttf", 30);
	_fontRoboto = TTF_OpenFont("ressources/font/roboto.ttf", 18);
	if (!_fontArcade || !_fontRoboto) {
		std::cerr << "Font not found: " << TTF_GetError() << std::endl;
		exit(84);
	}
	loadTexture();
	_winSize = {0, 0,
		    SDL_GetWindowSurface(_window)->w,
		    SDL_GetWindowSurface(_window)->h};
}

void LibSDL2::displayTitle()
{
	SDL_Rect titleZone = {(_winSize.w / 2) - 100, 20, 200, 50};

	_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, "ARCADE", _whiteC);
	_textureMap["title"] = SDL_CreateTextureFromSurface(_windowRenderer,
							    _loadSurface);
	SDL_FreeSurface(_loadSurface);
	SDL_RenderCopy(_windowRenderer, _textureMap["title"],
		       NULL, &titleZone);
}

void LibSDL2::displayTitle(std::string ttl)
{
	SDL_Rect titleZone = {(_winSize.w / 2) - 100, 20, 200, 50};

	_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, "ARCADE", _whiteC);
	_textureMap["title"] = SDL_CreateTextureFromSurface(_windowRenderer,
							    _loadSurface);
	SDL_FreeSurface(_loadSurface);
	SDL_RenderCopy(_windowRenderer, _textureMap["title"],
		       NULL, &titleZone);
	if (ttl.length() > 0) {
		_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, ttl.c_str(), _whiteC);
		titleZone.w = _loadSurface->w;
		titleZone.h = 30;
		titleZone.x = 30;
		titleZone.y = 30;
		_textureMap["usrName"] = SDL_CreateTextureFromSurface(_windowRenderer,
								      _loadSurface);
		SDL_FreeSurface(_loadSurface);
		SDL_RenderCopy(_windowRenderer, _textureMap["usrName"],
			       NULL, &titleZone);
	}
}

std::string LibSDL2::askUsername()
{
	SDL_Rect common = {(_winSize.w / 2) - 150, (_winSize.h / 2) - 20, 300, 40};
	SDL_Rect userName = {common.x + 10, common.y + 4, 128, common.h - 8};
	SDL_Rect enterUsrName = {common.x, common.y, common.w, common.h};
	SDL_Rect pos = {0, 64, 128, 32};
	std::string usrName("");

	SDL_StartTextInput();
	while (_event.key.keysym.sym != SDLK_RETURN) {
		if (SDL_PollEvent(&_event) == 1 &&
			(_event.type == SDL_TEXTINPUT ||
			 _event.type == SDL_KEYDOWN)) {
			if (_event.type == SDL_KEYDOWN &&
			    _event.key.keysym.sym == SDLK_BACKSPACE &&
			    usrName.length() > 0)
				usrName = usrName.substr(0, usrName.length() - 1);
			else if (_event.type == SDL_TEXTINPUT) {
				usrName += _event.text.text;
			}
		}
		SDL_RenderCopy(_windowRenderer, _textureMap["assets"], &pos, &enterUsrName);
		_loadSurface = TTF_RenderUTF8_Solid(_fontArcade, usrName.c_str(), _whiteC);
		if (usrName.length() > 0)
			userName.w = _loadSurface->w;
		_textureMap["usrName"] = SDL_CreateTextureFromSurface(_windowRenderer,
								      _loadSurface);
		SDL_FreeSurface(_loadSurface);
		SDL_RenderCopy(_windowRenderer, _textureMap["usrName"],
			       NULL, &userName);
		refreshDisplay();
	}
	SDL_StopTextInput();
	return usrName;
}

void LibSDL2::multiChoiceMenu(std::vector<std::string> list, int line,
			      int index, std::string title)
{
	int y = 200;
	int x = 50 + (360 * index);
	SDL_Color textColor;
	SDL_Rect nameZone = {x, y, 0, 30};
	std::stringstream ss;

	_loadSurface = TTF_RenderUTF8_Solid(_fontRoboto, title.c_str(), _whiteC);
	_textureMap[title] = SDL_CreateTextureFromSurface(_windowRenderer,
							  _loadSurface);
	nameZone.h = _loadSurface->h;
	nameZone.w = _loadSurface->w;
	SDL_FreeSurface(_loadSurface);
	SDL_RenderCopy(_windowRenderer, _textureMap[title],
		       NULL, &nameZone);
	for (int i = 0; i < (int)list.size(); i++) {
		nameZone.y += 30;
		if (i == line)
			textColor = _yellowC;
		else
			textColor = _whiteC;
		ss << i;
		_loadSurface = TTF_RenderUTF8_Solid(_fontRoboto,
						    list[i].c_str(), textColor);
		_textureMap[title + ss.str()] =
			SDL_CreateTextureFromSurface(_windowRenderer,
						     _loadSurface);
		nameZone.h = _loadSurface->h;
		nameZone.w = _loadSurface->w;
		SDL_FreeSurface(_loadSurface);
		SDL_RenderCopy(_windowRenderer, _textureMap[title + ss.str()],
			       NULL, &nameZone);
		ss.flush();
	}
}

void LibSDL2::playButton(int index)
{
	SDL_Rect play = {(_winSize.w / 2) - 72, _winSize.h - 100, 144, 48};
	SDL_Rect pos = {0, 0, 96, 32};

	if (index == 2) {
		pos = {0, 32, 96, 32};
		SDL_RenderCopy(_windowRenderer, _textureMap["assets"],
			       &pos, &play);
	} else {
		SDL_RenderCopy(_windowRenderer, _textureMap["assets"],
			       &pos, &play);
	}
}

int LibSDL2::getKey()
{
	if (SDL_PollEvent(&_event) == 1) {
		switch (_event.type) {
			case SDL_WINDOWEVENT:
				return _event.window.event;
			case SDL_KEYDOWN:
				return _event.key.keysym.sym;
			default:break;
		}

	}
	return 0;
}

ICore::Action LibSDL2::getAction()
{
	int key = getKey();

	switch (key) {
		case SDLK_UP:
			return MOVE_UP;
		case SDLK_RIGHT:
			return MOVE_RIGHT;
		case SDLK_DOWN:
			return MOVE_DOWN;
		case SDLK_LEFT:
			return MOVE_LEFT;
		case SDLK_a:
			return PREV_LIB;
		case SDLK_e:
			return NEXT_LIB;
		case SDLK_q:
			return PREV_GAME;
		case SDLK_d:
			return NEXT_GAME;
		case SDLK_m:
			return MENU;
		case SDLK_r:
			return RESET;
		case SDLK_RETURN:
			return ENTER;
		case SDL_WINDOWEVENT_CLOSE:
			return ESCAPE;
		case SDLK_ESCAPE:
			return ESCAPE;
		default:
			return NOTHING;
	}
}

void LibSDL2::loadTexture()
{
	_loadSurface = IMG_Load("ressources/assets/assets.png");
	_textureMap["assets"] = SDL_CreateTextureFromSurface(_windowRenderer,
							    _loadSurface);
	SDL_FreeSurface(_loadSurface);
}

std::string LibSDL2::getName()
{
	return _name;
}

void LibSDL2::close()
{
	for (auto const &texture : _textureMap)
		SDL_DestroyTexture(texture.second);
	SDL_DestroyRenderer(_windowRenderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
	TTF_CloseFont(_fontArcade);
	TTF_Quit();
}

extern "C" IDisplay *entryPoint()
{
	return new LibSDL2();
}