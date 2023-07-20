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
			this->_allowedMethod = rhs.GetAllowedMethods();
			this->_index = rhs.GetIndex();
			this->_redirection = rhs.GetRedirection();
			this->_root = rhs.GetRoot();
			this->_prefix = rhs.GetPrefix();
			this->_cgi = rhs.GetCgi();
			this->_errorPages = rhs.GetErrorPages();
			this->_autoIndex = rhs.GetAutoIndex();
			this->_bodySize = rhs.GetBodySize();
	}
	return *this;
}

std::ostream &	FT::operator<<( std::ostream & o, Location const & i )
{
	o 		<< "allowedMethod: "	<<	i.AllowedMethodsToStr() << std::endl
			<< "index: "			<<	i.IndexToStr() << std::endl
			<< "redirection: "		<<	i.GetRedirection() << std::endl
			<< "root: "				<<	i.GetRoot() << std::endl
			<< "prefix: "			<<	i.GetPrefix() << std::endl
			<< "cgi: "				<<	i.GetCgi() << std::endl
			<< "errorPages: "		<<	i.GetErrorPages() << std::endl
			<< "autoIndex: "		<<	i.GetAutoIndex() << std::endl
			<< "bodySize: "			<<	i.GetBodySize() << std::endl;
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
	LocationMethodsType	methods = GetAllowedMethods();
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

LocationMethodsType	FT::Location::GetAllowedMethods(void) const
{
	return (_allowedMethod);
}
LocationIndexType	FT::Location::GetIndex(void) const
{
	return (_index);
}
std::string	FT::Location::GetRedirection(void) const
{
	return (_redirection);
}
std::string	FT::Location::GetRoot(void) const
{
	return (_root);
}
std::string	FT::Location::GetPrefix(void) const
{
	return (_prefix);
}
FT::Cgi			FT::Location::GetCgi(void) const
{
	return (_cgi);
}
FT::ErrorPages	FT::Location::GetErrorPages(void) const
{
	return (_errorPages);
}
std::string	FT::Location::GetErrorPage(std::string code) const
{
	return (_errorPages.GetErrorPage(code));
}
bool		FT::Location::GetAutoIndex(void) const
{
	return (_autoIndex);
}
int			FT::Location::GetBodySize(void) const
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
