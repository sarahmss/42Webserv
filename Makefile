# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 17:02:33 by smodesto          #+#    #+#              #
#    Updated: 2023/09/24 14:09:15 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= webserv

SRC_PATH		= ./
INCLUDES_PATH	= ./
OBJS_PATH		= ./objects/

SRCS_FILES =	./main.cpp												\
				./srcs/Settings/Parser.cpp								\
				./srcs/Settings/ParserUtils.cpp							\
				./srcs/Directory_listing/Dir_listing.cpp				\
				./srcs/Settings/ServerConf.cpp							\
				./srcs/Settings/ServerParser.cpp						\
				./srcs/Settings/Directives/Cgi.cpp						\
				./srcs/Settings/Directives/ErrorPages.cpp				\
				./srcs/Settings/Directives/Listen.cpp					\
				./srcs/Settings/Directives/Location.cpp					\
				./srcs/Settings/Directives/LocationParser.cpp			\
				./srcs/Networking/Sockets/BindingSocket.cpp				\
				./srcs/Networking/Sockets/AcceptingSocket.cpp			\
				./srcs/Networking/Sockets/ListeningSocket.cpp			\
				./srcs/Networking/Sockets/SimpleSocket.cpp				\
				./srcs/Networking/SimpleServer.cpp						\
				./srcs/httpMessages/Utils.cpp							\
				./srcs/httpMessages/Request/Handler.cpp					\
				./srcs/httpMessages/Request/RequestParser.cpp			\
				./srcs/httpMessages/Request/Body.cpp					\
				./srcs/httpMessages/Response/ResponseBuilder.cpp		\
				./srcs/httpMessages/Response/Responder.cpp				\
				./srcs/httpMessages/Response/File_operation/File_op.cpp	\
				./srcs/Cgi_handler/Cgi_handler.cpp						\
				./srcs/multiplexing/PollHandler.cpp						\
				./srcs/Networking/WebServ.cpp							\
				./srcs/global.cpp



SRCS = $(addprefix $(SRC_PATH), $(SRCS_FILES))

OBJS_FILES	= $(patsubst %.cpp, %.o, $(SRCS_FILES))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_FILES))

HEADER_FILES	=	./srcs/Settings/Parser.hpp								\
					./srcs/Settings/ParserUtils.hpp							\
					./srcs/Settings/ServerConf.hpp							\
					./srcs/Settings/ServerParser.hpp						\
					./srcs/Settings/Directives/Cgi.hpp						\
					./srcs/Settings/Directives/ErrorPages.hpp				\
					./srcs/Directory_listing/Dir_listing.hpp				\
					./srcs/Settings/Directives/Listen.hpp					\
					./srcs/Settings/Directives/Location.hpp					\
					./srcs/Settings/Directives/LocationParser.hpp			\
					./srcs/Networking/Sockets/BindingSocket.hpp				\
					./srcs/Networking/Sockets/Sockets.hpp					\
					./srcs/Networking/Sockets/AcceptingSocket.hpp			\
					./srcs/Networking/Sockets/ListeningSocket.hpp			\
					./srcs/Networking/Sockets/SimpleSocket.hpp				\
					./srcs/Networking/SimpleServer.hpp						\
					./srcs/httpMessages/Utils.hpp							\
					./srcs/httpMessages/Request/Handler.hpp					\
					./srcs/httpMessages/Request/RequestParser.hpp			\
					./srcs/httpMessages/Request/Body.hpp					\
					./srcs/httpMessages/Response/ResponseBuilder.hpp		\
					./srcs/httpMessages/Response/Responder.hpp				\
					./srcs/httpMessages/Response/File_operation/File_op.hpp	\
					./srcs/Cgi_handler/Cgi_handler.hpp						\
					./srcs/multiplexing/PollHandler.hpp						\
					./srcs/Networking/WebServ.hpp							\
					./srcs/global.hpp

HEADERS = $(addprefix $(INCLUDES_PATH), $(HEADER_FILES))

CC			= g++
FLAGS		= -Wall -Wextra -Werror -g -std=c++98
INCLUDES	= -I $(INCLUDES_PATH)

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
			$(CC) $(OBJS) $(FLAGS) $(INCLUDES) -o $(NAME)

$(OBJS_PATH)%.o : $(SRC_PATH)%.cpp $(HEADERS)
			@mkdir -p objects/srcs/Settings/Directives
			@mkdir -p objects/srcs/Networking/Sockets
			@mkdir -p objects/srcs/httpMessages/Request
			@mkdir -p objects/srcs/httpMessages/Response
			@mkdir -p objects/srcs/httpMessages/Response/File_operation
			@mkdir -p objects/srcs/Cgi_handler
			@mkdir -p objects/srcs/Directory_listing
			@mkdir -p objects/srcs/multiplexing
			@mkdir -p logFile

			$(CC) $(FLAGS) -c  $< -o $@

clean:	clean_log
			@rm -f $(OBJS)
			@rm -rf $(OBJS_PATH)
			@echo cleaned!
			@rm -rf www/uploads

fclean:		clean
			@rm -f $(NAME)

re: fclean all

test_conf:
	@sudo python3 ./tests/misconfig/misconfig.py
	@sudo python3 ./tests/directives/listen/listen.py
	@sudo python3 ./tests/directives/server_name/server_name.py
	@sudo python3 ./tests/directives/client_body_size/client_body_size.py
	@sudo python3 ./tests/directives/allowed_methods/allowed_methods.py
	@sudo python3 ./tests/directives/index/index.py
test_debug:
	@sudo python3 ./tests/directives/allowed_methods/debug.py

test_methods:
	sudo python3 ./tests/methods/GET/get.py
	sudo python3 ./tests/methods/POST/post.py

test_all: test_conf
	@echo Done!

clean_log:
	@rm -rf logFile
	@rm -rf tests/__pycache__


.PHONY: all clean fclean re
