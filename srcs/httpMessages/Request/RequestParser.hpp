/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 20:59:02 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Body.hpp"
	class RequestParser
	{
		public:
			RequestParser();
			RequestParser(int socketFd);
			RequestParser( const RequestParser & src );
			~RequestParser();

			RequestParser& operator= (RequestParser const & rhs);

			bool		IsMultipartForm();
			std::string	getRequest() const;
			std::string	getMethod() const;
			std::string	getProtocolVersion() const;
			std::string	getUri() const;
			HeadersType	getHeaders() const;
			std::string	getHeader(const std::string &HeaderName) const;
			std::string	getBody() const;
			std::string	getServerName(void) const;
			std::string getTeste() const;
			int			getContentLength(void) const;

		private:
			int			_socketFd;
			std::string	_body;
			HeadersType	_headers;
			std::string	_method;
			std::string	_uri;
			std::string	_protocolVersion;
			std::string teste;
			bool		_multPart;

			void		_parseRequest(void);
			void		_parseBody(void);
			void		_parseRequestLine(std::string RequestLine);
			void		_parseHeader(const std::string Headers);
	};
	std::ostream &operator<<(std::ostream &o, const RequestParser &rhs);

#endif /* *************************************************** REQUESTPARSER_H */
