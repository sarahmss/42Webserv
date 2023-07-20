/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:37:23 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/20 14:35:51 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "./ParserUtils.hpp"
#include "./Server.hpp"
#include "./ServerParser.hpp"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>


# define ServerVecType std::vector<FT::Server>

namespace	FT
{
	class	Parser
	{
		public:
			Parser(void);
			Parser(Parser const& src);
			~Parser(void);

			Parser	&operator=(Parser const& rhs);

			void			exec(std::string filename);
			const			ServerVecType	&getServers(void) const;

		private:
			ServerVecType	_servers;
			std::ifstream	_fileStream;
			std::string		_line;

			void _parseFile(void);
			void _parseServerBlock(void);
	};

std::ostream &			operator<<( std::ostream & o, Parser const & i );
}

#endif //PARSER_HPP
