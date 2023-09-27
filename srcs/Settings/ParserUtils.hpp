/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:55:03 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/21 20:26:51 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSERUTILS_HPP
# define PARSERUTILS_HPP

# include <string>
# include <string.h>
# include <iostream>

	bool	IsValidLine(std::string &line);
	bool	IsComment(std::string &line);
	bool	IsEmpty(std::string &line);
	bool	OnlyOneArg(std::string &line);
	bool	IsValidBodySize(std::string &line);

	void	trim(std::string &line, const std::string Trim);
	void	ClearDirective(std::string &line, std::string directive);


#endif /* ***************************************************** PARSERUTILS_H */
