/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:44:41 by jinacio-          #+#    #+#             */
/*   Updated: 2023/09/09 11:55:01 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>
# include <sstream>

extern std::ofstream logFile;
extern clock_t start;
extern clock_t end;

extern void             sendMessageToLogFile( std::string message, bool errorOrNot, double duration);
extern std::string		concatenate_int(std::string s1, int n2);
extern std::string		concatenate_string(std::string s1, std::string s2);
#endif