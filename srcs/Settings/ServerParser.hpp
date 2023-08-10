/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 23:08:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/10 02:58:11 by smodesto         ###   ########.fr       */
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

#define SERVER_END "};"
#define LISTEN "listen"
#define SERVER_NAME "server_name"

namespace FT
{
	class ServerParser
	{
		public:
			ServerParser();
			ServerParser( ServerParser const & src );
			~ServerParser();

			ServerParser	&operator=( ServerParser const & rhs );

			void			launch(std::ifstream &ifstream, std::string line );
			FT::ServerConf		getServer(void) const;
			std::string		getLine(void) const;


		private:
			FT::ServerConf	_server;
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
}
#endif /* **************************************************** SERVERPARSER_H */
