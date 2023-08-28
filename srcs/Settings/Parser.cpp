/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:29:38 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/27 19:30:30 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
Parser::Parser(void)
{
	return ;
}

Parser::Parser(Parser const &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/


Parser::~Parser(void)
{
	return ;
}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Parser &Parser::operator=(Parser const &rhs)
{
	this->_servers = rhs._servers;
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Parser &i)
{
	for (size_t j = 0; j < i.getServers().size(); j++)
		o	<< i.getServers()[j] << std::endl;
	return o;
}



/*
** --------------------------------- METHODS ----------------------------------
*/


void	Parser::launch(std::string filename)
{
	_fileStream.open(filename.c_str(), std::ifstream::in);
	if (!_fileStream)
		throw (std::runtime_error("Failed to open Configuration file"));

	sendALog_parser("File was successfully opened | Parser->launch");
	_parseFile();
	_fileStream.close();

}

void	Parser::_parseFile(void)
{
	bool	empty = true;

	while (_fileStream.good())
	{
		std::getline(_fileStream, _line);
		if (IsValidLine(_line))
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

void	Parser::_parseServerBlock(void)
{
	ServerParser	newServer;

	newServer.launch(_fileStream, _line);
	_servers.push_back(newServer.getServer());
}

void Parser::start_logging_parser( void )
{

    this->_logFile.open("log.txt", std::ios::app);
	this->now = time(0);
	this->dt = ctime(&now);
	if (this->_logFile.is_open())
		this->_logFile << "Log starts"  << " | "<< this->dt << std::endl;


}

void Parser::sendALog_parser( std::string throw_message)
{
	this->now = time(0);
	this->dt = ctime(&now);
	_logFile << throw_message << " | " << this->dt << std::endl;
}


void Parser::closeALog_parser( void )
{
	_logFile.close();
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/



const ConfsVecType	&Parser::getServers(void) const
{
	return (_servers);
}

/* ************************************************************************** */
