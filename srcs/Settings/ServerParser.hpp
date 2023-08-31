/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:08:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/29 20:25:27 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERPARSER_HPP
# define SERVERPARSER_HPP

# include <sstream>
# include <fstream>
# include <string>
# include "ParserUtils.hpp"
# include "ServerConf.hpp"
# include "Directives/LocationParser.hpp"
# include "Directives/Listen.hpp"
# include "./../global.hpp"

#define SERVER_END "};"
#define LISTEN "listen"
#define SERVER_NAME "server_name"


	class ServerParser
	{
		public:
			ServerParser();
			ServerParser( ServerParser const & src );
			~ServerParser();

			ServerParser	&operator=( ServerParser const & rhs );

			void			launch(std::ifstream &ifstream, std::string line );
			ServerConf		getServer(void) const;
			std::string		getLine(void) const;


		private:
			ServerConf	_server;
			std::string	_line;

			void	_parseLocationBlock(std::ifstream &ifstream);
			void	_setServer(void);
			void	_checkListen(void);
			void	_setListen(Listen &listen);
			void	_setPort(Listen &listen, std::string port);
			void	_setServerName(void);
			void	_setErrorPage(void);
			void	_setCgi(void);
			void	_setRoot(void);
			void	_setBodySize(void);
	};
#endif /* **************************************************** SERVERPARSER_H */
