# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 17:02:33 by smodesto          #+#    #+#              #
#    Updated: 2023/07/21 15:21:15 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv

SRC_PATH		= ./
INCLUDES_PATH	= ./
OBJS_PATH		= ./objects/

SRCS_FILES =	./main.cpp										\
				./srcs/Settings/Parser.cpp						\
				./srcs/Settings/ParserUtils.cpp					\
				./srcs/Settings/Server.cpp						\
				./srcs/Settings/ServerParser.cpp				\
				./srcs/Settings/Directives/Cgi.cpp				\
				./srcs/Settings/Directives/ErrorPages.cpp		\
				./srcs/Settings/Directives/Listen.cpp			\
				./srcs/Settings/Directives/Location.cpp			\
				./srcs/Settings/Directives/LocationParser.cpp

SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

OBJS_FILES	= $(patsubst %.cpp, %.o, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_FILES))

HEADER_FILES	=	./srcs/Settings/Parser.hpp						\
					./srcs/Settings/ParserUtils.hpp					\
					./srcs/Settings/Server.hpp						\
					./srcs/Settings/ServerParser.hpp				\
					./srcs/Settings/Directives/Cgi.hpp				\
					./srcs/Settings/Directives/ErrorPages.hpp		\
					./srcs/Settings/Directives/Listen.hpp			\
					./srcs/Settings/Directives/Location.hpp			\
					./srcs/Settings/Directives/LocationParser.hpp

HEADERS = $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))

CC			= c++
FLAGS		= -Wall -Wextra -Werror -g -std=c++98
INCLUDES	= -I $(INCLUDES_PATH)

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			$(CC) $(OBJS) $(FLAGS) $(INCLUDES) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.cpp $(HEADERS)
			@mkdir -p objects
			@mkdir -p objects/Settings
			@mkdir -p objects/srcs/Settings/Directives

			$(CC) $(FLAGS) -c  $< -o $@

clean:
			@rm -f $(OBJS)
			@rm -rf $(OBJS_PATH)
			@echo cleaned!

fclean:		clean
			@rm -f $(NAME)

re: fclean all

test_misconfig:
	python3 ./tests/misconfig.py

.PHONY: all clean fclean re
