/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:56:00 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/24 17:37:28 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
# define RESPONDER_HPP

# include <iostream>
# include <string>
#include "./../../global.hpp"
# include <unistd.h>
# include "./ResponseBuilder.hpp"
# include "../Utils.hpp"

class Responder
{
	public:
		Responder(void);
		~Responder();

		void	launch(int clientSocket, std::string serverName, std::string sttsCode, strPairType Response, strPairType headerField);

		void	sendResponse(void);

	private:
		ResponseBuilder		_respBuilder;
		int					_clientSocket;
		std::string			_protocolVersion;
		std::string			_sttsCode;
		std::string			_reasonPhrase;
		std::string			_body;
		HeadersType			_header;

		void				_setBodyType(std::string path);

};

std::ostream &			operator<<( std::ostream & o, Responder const & i );

#endif /* ******************************************************* RESPONDER_H */
