/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:56:19 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPages.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ErrorPages::ErrorPages() { return ; }

ErrorPages::ErrorPages( const ErrorPages & src ) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ErrorPages::~ErrorPages() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ErrorPages &				ErrorPages::operator=( ErrorPages const & rhs )
{
	if ( this != &rhs )
	{
		this->_pages = rhs.getErrorPages();
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, ErrorPages const & i )
{
	ErrorPagesType					pages = i.getErrorPages();
	ErrorPagesType::const_iterator	it;

	for (it = pages.begin(); it != pages.end(); ++it)
		o << it->first << " - " << it->second << std::endl;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	ErrorPages::SetDefaultPages(void)
{
	_addDefaultPage("400");
	_addDefaultPage("403");
	_addDefaultPage("404");
	_addDefaultPage("405");
	_addDefaultPage("413");
	_addDefaultPage("500");
}

void	ErrorPages::addPage(std::string code, std::string path)
{
	_pages[code] = path;
}

bool	ErrorPages::hasPage(std::string code) const
{
	if (_pages.count(code) == 1)
		return true;
	return false;
}

void	ErrorPages::_addDefaultPage(std::string code)
{
	std::string	path(DEFAULTPATH + code + ".html");

	addPage(code, path);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

ErrorPagesType	ErrorPages::getErrorPages(void) const
{
	return (_pages);
}

std::string		ErrorPages::getErrorPage(std::string code) const
{
	if (hasPage(code))
		return _pages.at(code);
	return "";
}

/* ************************************************************************** */
