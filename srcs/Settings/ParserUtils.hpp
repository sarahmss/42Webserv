/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:55:03 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/20 13:54:06 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

# include <string>
# include <string.h>
# include <errno.h>
# include <iostream>

namespace FT
{
	bool	IsValidLine(std::string &line);
	bool	IsComment(std::string &line);
	bool	IsEmpty(std::string &line);
	bool	OnlyOneArg(std::string &line);
	bool	IsNumber(std::string &line);

	void	trim(std::string &line, const std::string Trim);
	void	ClearDirective(std::string &line, std::string directive);
}


#endif /* ***************************************************** PARSERUTILS_H */
