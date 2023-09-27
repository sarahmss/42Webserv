/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:01 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/25 20:06:29 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

LocationParser::LocationParser() { return; }

LocationParser::LocationParser( const LocationParser & src )
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

LocationParser::~LocationParser() { return; }


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

LocationParser	&LocationParser::operator=(LocationParser const &rhs)
{
	if ( this != &rhs )
	{
		this->_location = rhs.getLocation();
		this->_line = rhs.getLine();
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

void		LocationParser::launch(std::ifstream &fs, std::string line)
{
	_line = line;
	_setPrefix();
	while (fs.good())
	{
		std::getline(fs, _line);
		if (IsValidLine(_line))
		{
			if (_line == LOCATION_END)
				return;
			_setLocation();
		}
	}
}

void	LocationParser::_setPrefix(void)
{
	ClearDirective(_line, LOCATION_BEGIN);

	std::stringstream	lineStream(_line);
	std::string			prefix;

	std::getline(lineStream, prefix, ' ');
	_location.SetPrefix(prefix);
	std::getline(lineStream, prefix, ' ');
	trim(prefix, " \t");
	if (prefix != "{")
		throw (std::invalid_argument("Failed setting location [prefix]"));
}

void	LocationParser::_setLocation(void)
{
	if (!_line.find(ALLOWED_METHODS, 0))
		_setAllowedMethods();
	else if (!_line.find(INDEX, 0))
		_setIndex();
	else if (!_line.find(AUTOINDEX, 0))
		_setAutoindex();
	else if (!_line.find(BODY_SIZE, 0))
		_setBodySize();
	else if (!_line.find(ROOT, 0))
		_setRoot();
	else if (!_line.find(REDIRECTION, 0))
		_setRedirection();
	else if (!_line.find(ERROR_PAGE, 0))
		_setErrorPage();
	else if (!_line.find(CGI, 0))
		_setCgi();
	else
		throw (std::invalid_argument("Failed setting location [directives]"));
}

void	LocationParser::_setAllowedMethods(void)
{
	ClearDirective(_line, ALLOWED_METHODS);
	std::stringstream	lineStream(this->_line);
	std::string			allowedMethod;

	while (lineStream.good())
	{
		std::getline(lineStream, allowedMethod, ' ');
		_location.AddAllowedMethods(allowedMethod);
	}
}

void	LocationParser::_setIndex(void)
{
	ClearDirective(_line, INDEX);
	std::stringstream	lineStream(this->_line);
	std::string			index;

	while (lineStream.good())
	{
		std::getline(lineStream, index, ' ');
		_location.AddIndex(index);
	}
}

void	LocationParser::_setAutoindex(void)
{
	ClearDirective(_line, AUTOINDEX);

	if (_line == "on")
		_location.SetAutoIndex(true);
	else if (_line == "off")
		_location.SetAutoIndex(false);
	else
		throw (std::invalid_argument("Failed setting location [autoindex]. "));
}

void	LocationParser::_setBodySize(void)
{
	ClearDirective(_line, BODY_SIZE);

	if ((!IsValidBodySize(_line)) || (!OnlyOneArg(_line)))
		throw (std::invalid_argument("Failed setting location [body_size] "));
	else
		_location.SetBodySize(atoi(_line.c_str()));
}

void	LocationParser::_setRoot(void)
{
	ClearDirective(_line, ROOT);

	if ((_location.hasRootSet()) || (!OnlyOneArg(_line)) || _line.empty())
		throw (std::invalid_argument("Failed setting location [root]"));
	_location.SetRoot(_line);
}

void	LocationParser::_setRedirection(void)
{
	ClearDirective(_line, REDIRECTION);

	if ((_location.hasRedirectionSet()) || !OnlyOneArg(_line) || _line.empty())
		throw (std::invalid_argument("Failed setting location [redirection]"));
	_location.SetRedirection(_line);
}

void	LocationParser::_setErrorPage(void)
{
	ClearDirective(_line, ERROR_PAGE);

	if (OnlyOneArg(_line))
		throw(std::invalid_argument("Failed setting location [error_page]"));

	size_t		pos = _line.find_last_of(' ');
	std::string	pagePath = _line.substr(pos + 1);
	std::string	codes = _line.substr(0, pos);
	trim(codes, " \t");

	std::stringstream	codeStream(codes);

	while (codeStream.good())
	{
		std::getline(codeStream, codes, ' ');
		_location.AddErrorPage(codes, pagePath);
	}
}

void	LocationParser::_setCgi(void)
{
	ClearDirective(_line, CGI);

	if (OnlyOneArg(_line))
		throw(std::invalid_argument("Failed setting location [cgi]"));
	std::stringstream	lineStream(_line);
	std::string			extension;
	std::string			path;
	int					lineNumber = 1;

	while (lineStream.good())
	{
		switch (lineNumber)
		{
			case (1): {
				std::getline(lineStream, extension, ' ');
				break;
			}
			case (2): {
				std::getline(lineStream, path, ' ');
				break;
			}
			case (3):
				throw(std::invalid_argument("Failed setting location [cgi]"));
		}
		lineNumber += 1;
	}
	_location.AddCgi(extension, path);
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

Location		LocationParser::getLocation(void) const
{
	return (_location);
}

std::string			LocationParser::getLine(void) const
{
	return (_line);
}

/* ************************************************************************** */
