/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:41 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 21:44:26 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUESTPARSER_HPP
# define REQUESTPARSER_HPP

# include <iostream>
# include <string>
# include <map>

typedef std::map<std::string, std::string> HeadersType;

namespace FT
{
	class RequestParser
	{
		public:
			RequestParser(const std::string &request);
			~RequestParser();

			std::string	GetMethod() const;
			std::string	GetUri() const;
			HeadersType	GetHeaders() const;
			std::string	GetHeader(const std::string & HeaderName) const;
			std::string	GetBody() const;

		private:
			std::string	_request;
			std::string	_method;
			std::string	_uri;
			HeadersType	_headers;
			std::string	_body;

			void	parseRequest(void);
			void	parseHeader(const std::string& headersPart);
	};
}

#endif /* *************************************************** REQUESTPARSER_H */
