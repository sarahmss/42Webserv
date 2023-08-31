/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:44:41 by jinacio-          #+#    #+#             */
/*   Updated: 2023/08/29 21:13:46 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

extern std::ofstream logFile;
extern void sendMessageToLogFile( std::string message, bool errorOrNot, double duration);

#endif