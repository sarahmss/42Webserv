/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 23:12:06 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <stdlib.h>

# include "../Utils.hpp"

namespace FT
{
	class RequestParser
	{
		public:
			RequestParser();
			RequestParser( const std::string &request );
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
			std::string	_request;
			std::string	_body;
			HeadersType	_headers;
			std::string	_method;
			std::string	_uri;
			std::string	_protocolVersion;

			void		parseRequest(void);
			void		parseRequestLine(const std::string RequestLine);
			void		parseHeader(const std::string Headers);
			void		parseBody(const std::string Body);
			std::string	_HandleChunckedBody(const std::string Body);
			std::string	_ReadMessageBody(const std::string Body);
	};

}

std::ostream &operator<<(std::ostream &o, const FT::RequestParser &rhs);
#endif /* *************************************************** REQUESTPARSER_H */
