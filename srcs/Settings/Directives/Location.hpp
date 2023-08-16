/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:13:36 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:44:47 by smodesto         ###   ########.fr       */
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

typedef std::set<std::string> LocationMethodsType;
typedef std::vector<std::string> LocationIndexType;


	class Location
	{
		public:

			Location(void);
			Location( Location const & src );
			~Location(void);

			Location &		operator=( Location const & rhs );

			LocationMethodsType	getAllowedMethods(void) const;
			LocationIndexType	getIndex(void) const;
			std::string			getRedirection(void) const;
			std::string			getRoot(void) const;
			std::string			getPrefix(void) const;
			Cgi					getCgi(void) const;
			ErrorPages			getErrorPages(void) const;
			std::string			getErrorPage(std::string code) const;
			bool				getAutoIndex(void) const;
			int					getBodySize(void) const;

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
#endif /* ******************************************************** LOCATION_H */
