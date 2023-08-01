/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:37 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 21:44:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestParser.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

RequestParser::RequestParser()
{
}

RequestParser::RequestParser( const RequestParser & src )
{
}


/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

RequestParser::~RequestParser()
{
}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/

RequestParser &				RequestParser::operator=( RequestParser const & rhs )
{
	//if ( this != &rhs )
	//{
		//this->_value = rhs.getValue();
	//}
	return *this;
}

std::ostream &			operator<<( std::ostream & o, RequestParser const & i )
{
	//o << "Value = " << i.getValue();
	return o;
}


/*
** --------------------------------- METHODS ----------------------------------
*/

void	parseRequest(void)
{

}

void	parseHeader(const std::string& headersPart)
{

}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/


std::string	GetMethod() const
{
	return (_method);
}
std::string	GetUri() const
{
	return (_uri);
}
HeadersType	GetHeaders() const
{
	return (_headers);
}
std::string	GetHeader(const std::string & HeaderName) const
{
	return (_headers[HeaderName]);
}
std::string	GetBody() const
{
	return (_body);
}

/* ************************************************************************** */
