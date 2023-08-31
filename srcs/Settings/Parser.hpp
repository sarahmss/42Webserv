/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:37:23 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/28 21:04:38 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "./ParserUtils.hpp"
#include "./ServerParser.hpp"
#include "./../global.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>


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

		private:
			ConfsVecType	_servers;
			std::ifstream	_fileStream;
			std::string		_line;

			void _parseFile(void);
			void _parseServerBlock(void);
	};
	std::ostream &			operator<<( std::ostream & o, Parser const & i );


#endif //PARSER_HPP
