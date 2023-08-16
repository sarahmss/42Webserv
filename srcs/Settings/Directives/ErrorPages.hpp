/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:56:15 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:44:31 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORPAGES_HPP
# define ERRORPAGES_HPP

# include <iostream>
# include <string>
# include <map>
# define ErrorPagesType std::map<std::string, std::string>
# define DEFAULTPATH "./www/error/"


	class ErrorPages
	{
		public:

			ErrorPages();
			ErrorPages( ErrorPages const & src );
			~ErrorPages();

			ErrorPages &	operator=( ErrorPages const & rhs );

			ErrorPagesType	getErrorPages(void) const;
			std::string		getErrorPage(std::string code) const;
			void			SetDefaultPages(void);

			void			addPage(std::string code, std::string path);
			bool			hasPage(std::string code) const;


		private:
			ErrorPagesType	_pages;
			void			_addDefaultPage( std::string code );
	};

	std::ostream &			operator<<( std::ostream & o, ErrorPages const & i );

#endif /* ****************************************************** ERRORPAGES_H */
