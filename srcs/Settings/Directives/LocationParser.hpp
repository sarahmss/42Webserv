/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationParser.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:52:06 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/22 19:33:45 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONPARSER_HPP
# define LOCATIONPARSER_HPP

# include "../ParserUtils.hpp"
# include "Location.hpp"
# include <sstream>
# include <fstream>
# include <stdlib.h>

#define LOCATION_BEGIN "location"
#define LOCATION_END "}"
#define ROOT "root"
#define BODY_SIZE "client_body_size"
#define ALLOWED_METHODS "allowed_methods"
#define INDEX "index"
#define REDIRECTION "redirection"
#define AUTOINDEX "autoindex"
#define ERROR_PAGE "error_page"
#define CGI "cgi"

namespace FT
{
	class LocationParser
	{

		public:
			LocationParser();
			LocationParser( LocationParser const & src );
			~LocationParser();

			LocationParser &	operator=( LocationParser const & rhs );

			void				launch(std::ifstream &fs, std::string line);
			FT::Location		getLocation(void) const;
			std::string			getLine(void) const;


		private:
			FT::Location	_location;
			std::string		_line;

			void	_setLocation(void);
			void	_setAutoindex(void);
			void	_setAllowedMethods(void);
			void	_setErrorPage(void);
			void	_setPrefix(void);
			void	_setRoot(void);
			void	_setBodySize(void);
			void	_setIndex(void);
			void	_setRedirection(void);
			void	_setCgi(void);
	};
}

#endif /* ************************************************** LOCATIONPARSER_H */
