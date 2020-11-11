##
## EPITECH PROJECT, 2018
## Snake
## File description:
## Makefile
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
BOLD		=	"\033[1m"
ITALIC		=	"\033[3m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[0;36m"
RED			=	"\033[0;31m"
YELLOW		=	"\033[0;33m"
PURPLE		=	"\033[0;35m"

CC			=	g++

RM			=	rm -f

CPPFLAGS	=	-fpic -Wextra -Wall -Werror -std=c++14 -I../../include

LDFLAGS		=	-shared

SRC			=	Pacman.cpp

OBJS		=	$(SRC:.cpp=.o)

NAME		=	../lib_arcade_pacman.so

all: title $(NAME)

title:
	@$(ECHO) $(TEAL)$(BOLD)"[pacman compilation]"$(DEFAULT)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS) $(LDFLAGS) && \
	$(ECHO) $(YELLOW)$(BOLD)"-- READY:" $(NAME) "--"$(DEFAULT) || \
	$(ECHO) $(RED)$(BOLD)"/!\ FAILURE:" $(NAME) "/!\ "$(DEFAULT)

$(SRCS:.cpp=.d):%.d:%.cpp
	$(CC) $(CPPFLAGS) -MM $< >$@

.cpp.o:
	@$(CC) $(CPPFLAGS) -c $< -o $@ && \
	$(ECHO) $(GREEN)$(BOLD)"[OK]"$(DEFAULT)$(ITALIC) $< $(DEFAULT) || \
	$(ECHO) $(RED)"[KO]"$(DEFAULT)$(ITALIC) $< $(DEFAULT)

clean:
	@$(RM) $(OBJS)
	@$(ECHO) $(PURPLE)$(BOLD)"[clean]"$(DEFAULT)

fclean: clean
	@$(RM) $(NAME)
	@$(ECHO) $(PURPLE)$(BOLD)"[fclean]"$(DEFAULT)

re: fclean all

.PHONY: all clean fclean re
