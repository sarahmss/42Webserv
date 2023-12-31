/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/21 13:28:42 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Body.hpp"
# include "./../../global.hpp"
class RequestParser
{
	public:
		RequestParser();
		RequestParser(int socketFd);
		RequestParser( const RequestParser & src );
		~RequestParser();

		RequestParser& operator= (RequestParser const & rhs);

		bool		IsMultipartForm();
		FilesType	getFiles() const;
		std::string	getMethod() const;
		std::string	getProtocolVersion() const;
		std::string	getUri() const;
		HeadersType	getHeaders() const;
		std::string	getHeader(const std::string &HeaderName) const;
		std::string	getBody() const;
		std::string	getServerName(void) const;
		int			getContentLength(void) const;
		bool		getMultPart(void) const;

	private:
		int			_socketFd;
		FilesType	_files;
		std::string	_body;
		HeadersType	_headers;
		std::string	_method;
		std::string	_uri;
		std::string	_protocolVersion;
		bool		_multPart;

		void		_parseRequest(void);
		void		_parseBody(void);
		void		_parseRequestLine(std::string RequestLine);
		void		_parseHeader(const std::string Headers);
};
std::ostream &operator<<(std::ostream &o, const RequestParser &rhs);

#endif /* *************************************************** REQUESTPARSER_H */
