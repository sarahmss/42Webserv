/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:56:00 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/10 00:59:27 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
# define RESPONDER_HPP

# include <iostream>
# include <string>
#include "./ResponseBuilder.hpp"

class Responder
{
	public:

		Responder();
		Responder( Responder const & src );
		~Responder();

		Responder &		operator=( Responder const & rhs );

	private:
		std::string	_protocolVersion;
		std::string	_sttsCode;

};

std::ostream &			operator<<( std::ostream & o, Responder const & i );

#endif /* ******************************************************* RESPONDER_H */
