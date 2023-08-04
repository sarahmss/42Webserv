/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 21:08:41 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

#include "Body.hpp"

namespace FT
{
	class RequestParser
	{
		public:
			RequestParser();
			RequestParser(int socketFd);
			RequestParser( const RequestParser & src );
			~RequestParser();

			RequestParser& operator= (RequestParser const & rhs);

			std::string	GetRequest() const;
			std::string	GetMethod() const;
			std::string	GetUri() const;
			HeadersType	GetHeaders() const;
			std::string	GetHeader(const std::string &HeaderName) const;
			std::string	GetBody() const;
			std::string	GetProtocolVersion() const;
			std::string	GetServerName(void) const;

		private:
			int			_socketFd;
			std::string	_body;
			HeadersType	_headers;
			std::string	_method;
			std::string	_uri;
			std::string	_protocolVersion;

			void		_parseRequest(void);
			void		_parseBody(void);
			void		_parseRequestLine(std::string RequestLine);
			void		_parseHeader(const std::string Headers);
	};
}

std::ostream &operator<<(std::ostream &o, const FT::RequestParser &rhs);
#endif /* *************************************************** REQUESTPARSER_H */
