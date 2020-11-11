/*
** EPITECH PROJECT, 2018
** ICore
** File description:
** Declaration of ICore
*/

#ifndef ARCADE_ICORE_HPP
	#define ARCADE_ICORE_HPP


class ICore {
public:
	enum Action {
		NOTHING,
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		NEXT_LIB,
		PREV_LIB,
		NEXT_GAME,
		PREV_GAME,
		RESET,
		MENU,
		ENTER,
		ESCAPE
	};
};


#endif /* ARCADE_ICORE_HPP */
