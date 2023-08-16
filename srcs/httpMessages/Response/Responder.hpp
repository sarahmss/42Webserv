/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:56:00 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/15 20:21:30 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
# define RESPONDER_HPP

# include <iostream>
# include <string>
#include "./ResponseBuilder.hpp"
#include "../Utils.hpp"

class Responder
{
	public:
		Responder(void);
		Responder(int clientSocket, std::string serverName, std::string sttsCode, std::string body, strPairType headerField);
		~Responder();

		void	launch(void);

	private:
		ResponseBuilder		_respBuilder;
		std::string			_sttsCode;
		std::string			_reasonPhrase;
		std::string			_body;
		HeadersType			_header;
		int					_clientSocket;
};

std::ostream &			operator<<( std::ostream & o, Responder const & i );

#endif /* ******************************************************* RESPONDER_H */
