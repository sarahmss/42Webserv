/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:29:38 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/22 19:33:45 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
FT::Parser::Parser(void)
{
	return ;
}

FT::Parser::Parser(FT::Parser const &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


FT::Parser::~Parser(void)
{
	return ;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::Parser &FT::Parser::operator=(FT::Parser const &rhs)
{
	this->_servers = rhs._servers;
	return (*this);
}

std::ostream &FT::operator<<(std::ostream &o, const FT::Parser &i)
{
	for (size_t j = 0; j < i.getServers().size(); j++)
		o	<< i.getServers()[j] << std::endl;
	return o;
}



/*
** --------------------------------- METHODS ----------------------------------
*/


void	FT::Parser::launch(std::string filename)
{
	_fileStream.open(filename.c_str(), std::ifstream::in);
	if (!_fileStream)
		throw (std::runtime_error("Failed to open Configuration file"));
	_parseFile();
	_fileStream.close();

}

void	FT::Parser::_parseFile(void)
{
	bool	empty = true;

	while (_fileStream.good())
	{
		std::getline(_fileStream, _line);
		if (FT::IsValidLine(_line))
		{
			if (_line == "server {")
				_parseServerBlock();
			else
				throw (std::invalid_argument("Failed setting server block"));
			empty = false;
		}
	}
	if (empty == true)
		throw (std::logic_error("Empty file"));
}

void	FT::Parser::_parseServerBlock(void)
{
	FT::ServerParser	newServer;

	newServer.launch(_fileStream, _line);
	_servers.push_back(newServer.getServer());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

const ServerVecType	&FT::Parser::getServers(void) const
{
	return (_servers);
}

/* ************************************************************************** */
