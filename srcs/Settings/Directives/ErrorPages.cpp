/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:56:19 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPages.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::ErrorPages::ErrorPages() { return ; }

FT::ErrorPages::ErrorPages( const ErrorPages & src ) { *this = src; }

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::ErrorPages::~ErrorPages() { return ; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::ErrorPages &				FT::ErrorPages::operator=( ErrorPages const & rhs )
{
	if ( this != &rhs )
	{
		this->_pages = rhs.getErrorPages();
	}
	return *this;
}

std::ostream &			FT::operator<<( std::ostream & o, FT::ErrorPages const & i )
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

void	FT::ErrorPages::SetDefaultPages(void)
{
	_addDefaultPage("400");
	_addDefaultPage("403");
	_addDefaultPage("404");
	_addDefaultPage("405");
	_addDefaultPage("413");
	_addDefaultPage("500");
}

void	FT::ErrorPages::addPage(std::string code, std::string path)
{
	_pages[code] = path;
}

bool	FT::ErrorPages::hasPage(std::string code) const
{
	if (_pages.count(code) == 1)
		return true;
	return false;
}

void	FT::ErrorPages::_addDefaultPage(std::string code)
{
	std::string	path(DEFAULTPATH + code + ".html");

	addPage(code, path);
}
/*
** --------------------------------- ACCESSOR ---------------------------------
*/

ErrorPagesType	FT::ErrorPages::getErrorPages(void) const
{
	return (_pages);
}

std::string		FT::ErrorPages::getErrorPage(std::string code) const
{
	if (hasPage(code))
		return _pages.at(code);
	return "";
}

/* ************************************************************************** */
