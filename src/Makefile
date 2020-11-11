##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## compile games - libs - project
##

ECHO	=	/bin/echo -e
DEFAULT =	"\033[00m"
BOLD	=	"\033[1m"
ITALIC	=	"\033[3m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[0;36m"
RED		=	"\033[0;31m"
YELLOW	=	"\033[0;33m"
PURPLE	=	"\033[0;35m"
BLUE	=	"\033[0;34m"

CC			=	g++

RM			=	rm -f

CPPFLAGS	=	-Wextra -Wall -Werror --std=c++14 -I../include -g

LDFLAGS 	=	-ldl

SRCS		=	main.cpp \
				Core.cpp

NAME		=	../arcade

OBJS		=	$(SRCS:.cpp=.o)

all: title $(NAME)

title:
	@$(ECHO) $(BLUE)$(BOLD)"[Arcade compilation]"$(DEFAULT)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && \
	$(ECHO) $(YELLOW)$(BOLD)"-- READY:" $(NAME) "--"$(DEFAULT) || \
	$(ECHO) $(RED)$(BOLD)"/!\ FAILURE:" $(NAME) "/!\ "$(DEFAULT)$

.cpp.o:
	@$(CC) $(CPPFLAGS) -c $< -o $@ && \
	$(ECHO) $(GREEN)$(BOLD)"[OK]"$(DEFAULT)$(ITALIC) $< $(DEFAULT) || \
	$(ECHO) $(RED)"[KO]"$(DEFAULT)$(ITALIC) $< $(DEFAULT)

clean:
	@$(RM) $(OBJS)
	@$(ECHO) $(PURPLE)$(BOLD)"[clean]"$(DEFAULT)

fclean: clean
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@$(ECHO) $(PURPLE)$(BOLD)"[fclean]"$(DEFAULT)

re: fclean all

.PHONY: all clean fclean re