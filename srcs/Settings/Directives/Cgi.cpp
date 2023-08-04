/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:12:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:09:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Cgi::Cgi(){ return; }

FT::Cgi::Cgi( const Cgi & src ) { *this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Cgi::~Cgi() { return ;}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::Cgi &				FT::Cgi::operator=( Cgi const & rhs )
{
	if ( this != &rhs )
	{
		this->_programs = rhs.getPrograms();
	}
	return *this;
}

std::ostream &			FT::operator<<( std::ostream & o, FT::Cgi const & i )
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

size_t	FT::Cgi::size(void) const
{
	return (_programs.size());
}
void	FT::Cgi::addProgram(std::string extension, std::string path)
{
	_programs[extension]= path;
}

bool	FT::Cgi::hasExtension(std::string extension) const
{
	if (_programs.count(extension) == 1)
		return true;
	return false;
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/
CgiProgramType	FT::Cgi::getPrograms() const
{
	return _programs;
}

std::string		FT::Cgi::getProgram(std::string extension) const
{
	if (hasExtension(extension))
		return (_programs.at(extension));
	return "";
}


/* ************************************************************************** */
