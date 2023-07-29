# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 17:02:33 by smodesto          #+#    #+#              #
#    Updated: 2023/07/22 19:46:33 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv

SRC_PATH		= ./
INCLUDES_PATH	= ./
OBJS_PATH		= ./objects/

SRCS_FILES =	./main.cpp										\
				./srcs/Response/ResponseBuilder.cpp				\
				./srcs/File_operation/File_op.cpp				\
				./srcs/Settings/Parser.cpp						\
				./srcs/Settings/ParserUtils.cpp					\
				./srcs/Settings/Server.cpp						\
				./srcs/Settings/ServerParser.cpp				\
				./srcs/Settings/Directives/Cgi.cpp				\
				./srcs/Settings/Directives/ErrorPages.cpp		\
				./srcs/Settings/Directives/Listen.cpp			\
				./srcs/Settings/Directives/Location.cpp			\
				./srcs/Settings/Directives/LocationParser.cpp	\
				./srcs/Networking/Sockets/BindingSocket.cpp		\
				./srcs/Networking/Sockets/ConnectingSocket.cpp	\
				./srcs/Networking/Sockets/ListeningSocket.cpp	\
				./srcs/Networking/Sockets/SimpleSocket.cpp		\
				./srcs/Networking/SimpleServer.cpp				\
				./srcs/Networking/WebServ.cpp


SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

OBJS_FILES	= $(patsubst %.cpp, %.o, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_FILES))

HEADER_FILES	=	./srcs/Settings/Parser.hpp						\
					./srcs/Settings/ParserUtils.hpp					\
					./srcs/Settings/Server.hpp						\
					./srcs/File_operation/File_op.hpp				\
					./srcs/Response/ResponseBuilder.hpp				\
					./srcs/Settings/ServerParser.hpp				\
					./srcs/Settings/Directives/Cgi.hpp				\
					./srcs/Settings/Directives/ErrorPages.hpp		\
					./srcs/Settings/Directives/Listen.hpp			\
					./srcs/Settings/Directives/Location.hpp			\
					./srcs/Settings/Directives/LocationParser.hpp	\
					./srcs/Networking/Sockets/BindingSocket.hpp		\
					./srcs/Networking/Sockets/Sockets.hpp			\
					./srcs/Networking/Sockets/ConnectingSocket.hpp	\
					./srcs/Networking/Sockets/ListeningSocket.hpp	\
					./srcs/Networking/Sockets/SimpleSocket.hpp		\
					./srcs/Networking/SimpleServer.hpp				\
					./srcs/Networking/WebServ.hpp


HEADERS = $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))

CC			= c++
FLAGS		= -Wall -Wextra -Werror -g -std=c++98
INCLUDES	= -I $(INCLUDES_PATH)

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			$(CC) $(OBJS) $(FLAGS) $(INCLUDES) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.cpp $(HEADERS)
			@mkdir -p objects
			@mkdir -p objects/srcs/Settings/Directives
			@mkdir -p objects/srcs/Networking/Sockets
			@mkdir -p objects/srcs/File_operation
			@mkdir -p objects/srcs/Response


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
