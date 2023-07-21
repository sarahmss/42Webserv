/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:54:57 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/21 15:07:29 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserUtils.hpp"

void	FT::trim(std::string &line, const std::string Trim)
{
	line.erase(0, line.find_first_not_of(Trim));
	line.erase(line.find_last_not_of(Trim) + 1);
}

bool	FT::IsComment(std::string &line)
{
	FT::trim(line, " \t");
	FT::trim(line, " ");

	if (line.find('#') == 0)
		return true;
	return false;
}

bool	FT::IsEmpty(std::string &line)
{
	FT::trim(line, " \t");
	FT::trim(line, " ");
	return (line == "");
}

bool	FT::IsValidLine(std::string &line)
{
	if (FT::IsEmpty(line))
		return false;
	if (FT::IsComment(line))
		return false;
	return (true);
}

void	FT::ClearDirective(std::string &line, std::string directive)
{
	line.erase(0, strlen(directive.c_str()));
	trim(line, " \t");
}

bool	FT::OnlyOneArg(std::string &line)
{
	if (line.find(' ') != std::string::npos)
		return (true);
	if (line.find('\t') != std::string::npos)
		return (true);
	return (false);
}

bool	FT::IsNumber(std::string &line)
{
	return (line.find_first_not_of("0123456789") == std::string::npos);
}

/* ************************************************************************** */
