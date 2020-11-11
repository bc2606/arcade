/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** main
*/

#include <vector>
#include <string>
#include "interface/IGame.hpp"
#include "interface/IDisplay.hpp"
#include "DLLoader.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		exit(84);
	Core core(av[1]);
	core.menu();
	core.game();
	return 0;
}