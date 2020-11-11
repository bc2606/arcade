##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## compile games - libs - project
##

all: core graphicals games

core:
	make -C src

graphicals:
	make -C lib/caca
	make -C lib/sdl2
	make -C lib/opengl

games:
	make -C games/nibbler
	make -C games/pacman

clean:
	make clean -C src
	make clean -C lib/caca
	make clean -C lib/sdl2
	make clean -C lib/opengl
	make clean -C games/nibbler
	make clean -C games/pacman

fclean:
	make fclean -C src
	make fclean -C lib/caca
	make fclean -C lib/sdl2
	make fclean -C lib/opengl
	make fclean -C games/nibbler
	make fclean -C games/pacman

re:
	make re -C src
	make re -C lib/caca
	make re -C lib/sdl2
	make re -C lib/opengl
	make re -C games/nibbler
	make re -C games/pacman

.PHONY: all core graphicals games clean fclean re