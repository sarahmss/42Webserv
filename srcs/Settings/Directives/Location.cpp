/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:13:31 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/11 22:14:14 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

FT::Location::Location():	_allowedMethod(LocationMethodsType()),
							_index(LocationIndexType()),
							_redirection(""),
							_root(""),
							_prefix(""),
							_cgi(FT::Cgi()),
							_errorPages(FT::ErrorPages()),
							_autoIndex(false),
							_bodySize(0)
{
	_allowedMethod.insert("GET");
}

FT::Location::Location( const Location & src ) {*this = src; }


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::Location::~Location() { return ;}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

FT::Location &	FT::Location::operator=( Location const & rhs )
{
	if ( this != &rhs )
	{
			this->_allowedMethod = rhs.getAllowedMethods();
			this->_index = rhs.getIndex();
			this->_redirection = rhs.getRedirection();
			this->_root = rhs.getRoot();
			this->_prefix = rhs.getPrefix();
			this->_cgi = rhs.getCgi();
			this->_errorPages = rhs.getErrorPages();
			this->_autoIndex = rhs.getAutoIndex();
			this->_bodySize = rhs.getBodySize();
	}
	return *this;
}

std::ostream &	FT::operator<<( std::ostream & o, Location const & i )
{
	o 		<< "allowedMethod: "	<<	i.AllowedMethodsToStr() << std::endl
			<< "index: "			<<	i.IndexToStr() << std::endl
			<< "redirection: "		<<	i.getRedirection() << std::endl
			<< "root: "				<<	i.getRoot() << std::endl
			<< "prefix: "			<<	i.getPrefix() << std::endl
			<< "cgi: "				<<	i.getCgi() << std::endl
			<< "errorPages: "		<<	i.getErrorPages() << std::endl
			<< "autoIndex: "		<<	i.getAutoIndex() << std::endl
			<< "bodySize: "			<<	i.getBodySize() << std::endl;
	return o;
}

bool	FT::Location::operator>(Location const &rhs) const
{
	return (this->_prefix > rhs._prefix);
}
bool	FT::Location::operator>=(Location const &rhs) const
{
	return (this->_prefix >= rhs._prefix);
}
bool	FT::Location::operator<(Location const &rhs) const
{
	return (this->_prefix < rhs._prefix);
}
bool	FT::Location::operator<=(Location const &rhs) const
{
	return (this->_prefix <= rhs._prefix);
}
bool	FT::Location::operator==(Location const &rhs) const
{
	return (this->_prefix == rhs._prefix);
}
bool	FT::Location::operator!=(Location const &rhs) const
{
	return (this->_prefix != rhs._prefix);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

std::string	FT::Location::AllowedMethodsToStr(void) const
{
	std::string			str;
	LocationMethodsType	methods = getAllowedMethods();
	LocationMethodsType::const_iterator	it;

	for (it = methods.begin(); it != methods.end(); ++it)
		str += (*it + "");
	return (str);
}

std::string	FT::Location::IndexToStr(void) const
{
	std::string	str;

	for (size_t i = 0; i < _index.size(); i++)
		str += _index[i];
	return (str);
}

bool	FT::Location::hasErrorPage(std::string code) const
{
	return(_errorPages.hasPage(code));
}
bool	FT::Location::hasRedirectionSet(void) const
{
	return (!_redirection.empty());
}
bool	FT::Location::hasRootSet(void) const
{
	return(!_root.empty());
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

LocationMethodsType	FT::Location::getAllowedMethods(void) const
{
	return (_allowedMethod);
}
LocationIndexType	FT::Location::getIndex(void) const
{
	return (_index);
}
std::string	FT::Location::getRedirection(void) const
{
	return (_redirection);
}
std::string	FT::Location::getRoot(void) const
{
	return (_root);
}
std::string	FT::Location::getPrefix(void) const
{
	return (_prefix);
}
FT::Cgi			FT::Location::getCgi(void) const
{
	return (_cgi);
}
FT::ErrorPages	FT::Location::getErrorPages(void) const
{
	return (_errorPages);
}
std::string	FT::Location::getErrorPage(std::string code) const
{
	return (_errorPages.getErrorPage(code));
}
bool		FT::Location::getAutoIndex(void) const
{
	return (_autoIndex);
}
int			FT::Location::getBodySize(void) const
{
	return (_bodySize);
}

void	FT::Location::AddAllowedMethods(std::string allowedMethods)
{
	_allowedMethod.insert(allowedMethods);
}
void	FT::Location::AddIndex(std::string index)
{
	_index.push_back(index);
}
void	FT::Location::AddCgi(std::string extension, std::string programPath)
{
	_cgi.addProgram(extension, programPath);
}
void	FT::Location::AddErrorPage(std::string code, std::string PagePath)
{
	_errorPages.addPage(code, PagePath);
}
void	FT::Location::SetRedirection(std::string redirection)
{
	_redirection = redirection;
}

void	FT::Location::SetRoot(std::string root)
{
	_root = root;
}

void	FT::Location::SetPrefix(std::string prefix)
{
	_prefix = prefix;
}

void	FT::Location::SetAutoIndex(bool autoindex)
{
	_autoIndex = autoindex;
}

void	FT::Location::SetBodySize(int bodySize)
{
	_bodySize = bodySize;
}

/* ************************************************************************** */
