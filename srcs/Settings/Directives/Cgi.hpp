/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 22:13:02 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/11 22:13:04 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include <iostream>
# include <string>
# include <map>


#define CgiProgramType std::map<std::string, std::string>

namespace FT
{
	class Cgi
	{
		public:

			Cgi();
			Cgi( Cgi const & src );
			~Cgi();

			Cgi &		operator=( Cgi const & rhs );

			CgiProgramType	GetPrograms() const;
			std::string		GetProgram(std::string extension) const;

			size_t			size(void) const;
			void			addProgram(std::string extension, std::string path);
			bool			hasExtension(std::string extension) const;

		private:
			CgiProgramType	_programs;
	};

	std::ostream &			operator<<( std::ostream & o, Cgi const & i );

}

#endif /* ************************************************************* CGI_H */
