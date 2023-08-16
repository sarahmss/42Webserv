/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:12:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Cgi::Cgi(){ return; }

Cgi::Cgi( const Cgi & src ) { *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Cgi::~Cgi() { return ;}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Cgi &				Cgi::operator=( Cgi const & rhs )
{
	if ( this != &rhs )
	{
		this->_programs = rhs.getPrograms();
	}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, Cgi const & i )
{
	CgiProgramType					pages = i.getPrograms();
	CgiProgramType::const_iterator	it;

	for (it = pages.begin(); it != pages.end(); ++it)
		o << it->first << " - " << it->second << std::endl;
	return o;
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

size_t	Cgi::size(void) const
{
	return (_programs.size());
}
void	Cgi::addProgram(std::string extension, std::string path)
{
	_programs[extension]= path;
}

bool	Cgi::hasExtension(std::string extension) const
{
	if (_programs.count(extension) == 1)
		return true;
	return false;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/
CgiProgramType	Cgi::getPrograms() const
{
	return _programs;
}

std::string		Cgi::getProgram(std::string extension) const
{
	if (hasExtension(extension))
		return (_programs.at(extension));
	return "";
}


/* ************************************************************************** */
