/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:13:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/20 14:18:55 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <iostream>
# include <string>
# include <vector>
# include <set>
# include "Cgi.hpp"
# include "ErrorPages.hpp"

# define LocationMethodsType std::set<std::string>
# define LocationIndexType std::vector<std::string>

namespace FT
{
	class Location
	{
		public:

			Location(void);
			Location( Location const & src );
			~Location(void);

			Location &		operator=( Location const & rhs );

			LocationMethodsType	GetAllowedMethods(void) const;
			LocationIndexType	GetIndex(void) const;
			std::string			GetRedirection(void) const;
			std::string			GetRoot(void) const;
			std::string			GetPrefix(void) const;
			Cgi					GetCgi(void) const;
			ErrorPages			GetErrorPages(void) const;
			std::string			GetErrorPage(std::string code) const;
			bool				GetAutoIndex(void) const;
			int					GetBodySize(void) const;

			void	AddAllowedMethods(std::string allowedMethods);
			void	AddIndex(std::string index);
			void	AddCgi(std::string extension, std::string programPath);
			void	AddErrorPage(std::string code, std::string PagePath);
			void	SetRedirection(std::string redirection);
			void	SetRoot(std::string root);
			void	SetPrefix(std::string prefix);
			void	SetAutoIndex(bool autoindex);
			void	SetBodySize(int bodySize);

			std::string	AllowedMethodsToStr(void) const;
			std::string	IndexToStr(void) const;

			bool	hasErrorPage(std::string code) const;
			bool	hasRedirectionSet(void) const;
			bool	hasRootSet(void) const;

			bool	operator>(Location const &rhs) const;
			bool	operator>=(Location const &rhs) const;
			bool	operator<(Location const &rhs) const;
			bool	operator<=(Location const &rhs) const;
			bool	operator==(Location const &rhs) const;
			bool	operator!=(Location const &rhs) const;

		private:
			LocationMethodsType	_allowedMethod;
			LocationIndexType	_index;
			std::string			_redirection;
			std::string			_root;
			std::string			_prefix;
			Cgi					_cgi;
			ErrorPages			_errorPages;
			bool				_autoIndex;
			int					_bodySize;


	};

	std::ostream &			operator<<( std::ostream & o, Location const & i );
}
#endif /* ******************************************************** LOCATION_H */
