/*
** EPITECH PROJECT, 2018
** libcaca
** File description:
** Implementation of libcaca
*/

#include "LibCaca.hpp"

LibCaca::LibCaca() = default;

LibCaca::~LibCaca()
{
	close();
}

void LibCaca::drawScore(int score)
{
	int size = 0;
	char buf[10];

	size = sprintf(buf, "%d", score);
	caca_printf(_canvas, caca_get_canvas_width(_canvas) - 8, 1, "Score");
	caca_printf(_canvas, caca_get_canvas_width(_canvas) - (size + 3), 2, "%s", buf);
}

void LibCaca::drawBoard(std::vector<std::string> board)
{
	auto x = (int)((caca_get_canvas_width(_canvas) / 2) - (board[0].size() / 2));
	auto y = (int)((caca_get_canvas_height(_canvas) / 2) - (board.size() / 2));

	for (auto const &line : board) {
		caca_printf(_canvas, x, y++, "%s", line.c_str());
	}
}

void LibCaca::refreshDisplay()
{
	caca_refresh_display(_display);
	caca_clear_canvas(_canvas);
}

void LibCaca::initScreen()
{
	_canvas = caca_create_canvas(80, 40);
	_display = caca_create_display(_canvas);
	caca_set_display_title(_display, "Arcade de Zarok");
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
}

void LibCaca::displayTitle()
{
	caca_printf(_canvas, caca_get_canvas_width(_canvas) / 2 - 3, 1,
		    "Arcade");
}

void LibCaca::displayTitle(std::string ttl)
{
	caca_printf(_canvas, caca_get_canvas_width(_canvas) / 2 - 3, 1,
		    "Arcade");
	caca_printf(_canvas, 2, 1, ttl.c_str());
}

std::string LibCaca::askUsername()
{
	int x = (caca_get_canvas_width(_canvas) / 2) - 10;
	int y = caca_get_canvas_height(_canvas) / 2;
	char key[2];
	key[1] = 0;
	std::string usrName("");

	while ((key[0] = (char)getKey()) != 13) {
		if (key[0] == 8 && usrName.length() > 0)
			usrName = usrName.substr(0, usrName.length() - 1);
		else
			usrName += key;
		caca_draw_thin_box(_canvas, x, y, 20, 3);
		caca_printf(_canvas, x + 2, y, "Username");
		caca_printf(_canvas, x + 2, y + 1, usrName.c_str());
		refreshDisplay();
	}
	return usrName;
}

void LibCaca::multiChoiceMenu(std::vector<std::string> list, int line,
			      int index, std::string title)
{
	int y = 6;
	int x = 3 + (25 * index);

	caca_printf(_canvas, x + 1, 5, title.c_str());
	for (int i = 0; i < (int)list.size(); i++) {
		if (i == line) {
			caca_set_color_ansi(_canvas, CACA_BLACK, CACA_WHITE);
			caca_printf(_canvas, x, y++, list[i].c_str());
			caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
		} else {
			caca_printf(_canvas, x, y++, list[i].c_str());
		}
	}
}

void LibCaca::playButton(int index)
{
	int x = (caca_get_canvas_width(_canvas) / 2) - 4;
	int y = caca_get_canvas_height(_canvas) - 4;

	caca_draw_box(_canvas, x, y, 8, 3, '=');
	if (index == 2)
		caca_set_color_ansi(_canvas, CACA_BLACK, CACA_WHITE);
	caca_printf(_canvas, x + 2, y + 1, "PLAY");
	caca_set_color_ansi(_canvas, CACA_WHITE, CACA_BLACK);
}

int LibCaca::getKey()
{
	int key = 0;
	int event = 0;

	event = caca_get_event(_display, CACA_EVENT_KEY_PRESS, &_event, 0);
	if (event == CACA_EVENT_KEY_PRESS)
		key = caca_get_event_key_ch(&_event);
	return key;
}

ICore::Action LibCaca::getAction()
{
	int key = getKey();

	switch (key) {
		case 273:
			return MOVE_UP;
		case 276:
			return MOVE_RIGHT;
		case 274:
			return MOVE_DOWN;
		case 275:
			return MOVE_LEFT;
		case 97:
			return PREV_LIB;
		case 101:
			return NEXT_LIB;
		case 13:
			return ENTER;
		case 27:
			return ESCAPE;
		default:
			return NOTHING;
	}
}

std::string LibCaca::getName()
{
	return _name;
}

void LibCaca::close()
{
	caca_free_display(_display);
}

extern "C" IDisplay *entryPoint()
{
	return new LibCaca();
}