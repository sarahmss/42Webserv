/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:37:23 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/27 19:29:51 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "./ParserUtils.hpp"
#include "./ServerParser.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <unistd.h>


typedef std::vector<ServerConf> ConfsVecType;
	class	Parser
	{
		public:
			Parser(void);
			Parser(Parser const& src);
			~Parser(void);

			Parser	&operator=(Parser const& rhs);

			void			launch(std::string filename);
			const			ConfsVecType	&getServers(void) const;
			void			start_logging_parser( void );
			void 			sendALog_parser( std::string throw_message );
			void			closeALog_parser( void );

		private:
			ConfsVecType	_servers;
			std::ifstream	_fileStream;
			std::ofstream	_logFile;
			std::string		_line;
			time_t now;
			char *dt;

			void _parseFile(void);
			void _parseServerBlock(void);
	};
	std::ostream &			operator<<( std::ostream & o, Parser const & i );


#endif //PARSER_HPP
