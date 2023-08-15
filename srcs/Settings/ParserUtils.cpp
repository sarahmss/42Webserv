/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:54:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/14 19:39:25 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserUtils.hpp"

void	trim(std::string &line, const std::string Trim)
{
	line.erase(0, line.find_first_not_of(Trim));
	line.erase(line.find_last_not_of(Trim) + 1);
}

bool	IsComment(std::string &line)
{
	trim(line, " \t");
	trim(line, " ");

	if (line.find('#') == 0)
		return true;
	return false;
}

bool	IsEmpty(std::string &line)
{
	trim(line, " \t");
	trim(line, " ");
	return (line == "");
}

bool	IsValidLine(std::string &line)
{
	if (IsEmpty(line))
		return false;
	if (IsComment(line))
		return false;
	return (true);
}

void	ClearDirective(std::string &line, std::string directive)
{
	line.erase(0, strlen(directive.c_str()));
	trim(line, " \t");
}

/*
	@brief: returns true if line contains only one argument
*/
bool	OnlyOneArg(std::string &line)
{
	if ((line.find(' ') == std::string::npos) &&
		(line.find('\t') == std::string::npos))
		return (true);
	return (false);
}

bool	IsValidBodySize(std::string &line)
{
	return (line.find_first_not_of("0123456789mM") == std::string::npos);
}

/* ************************************************************************** */
