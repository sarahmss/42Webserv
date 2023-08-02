/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/01 23:46:39 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <stdlib.h>
#include <string.h>
# include "../Utils.hpp"
#include <sys/socket.h>


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

		private:
			int			_socketFd;
			std::string	_request;
			std::string	_body;
			HeadersType	_headers;
			std::string	_method;
			std::string	_uri;
			std::string	_protocolVersion;

			void		parseRequest(void);
			std::string	_GetRequestLine(void);
			void		parseRequestLine(std::string RequestLine);
			void		parseHeader(const std::string Headers);
			void		parseBody();
			void		_HandleChunckedBody();
			void		_ReadMessageBody();
			void		_GetBodyMessage(std::string &Body);
			bool		_IsMultipartFormData();
			void		_ClearFooter(std::string &Body);
			void		_ClearHeader(std::string &Body);
			void		_GetFileName(std::string header);
	};
}

std::ostream &operator<<(std::ostream &o, const FT::RequestParser &rhs);
#endif /* *************************************************** REQUESTPARSER_H */
