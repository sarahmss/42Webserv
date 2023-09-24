/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AcceptingSocketSocket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 12:59:55 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/31 13:00:22 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CONNECTIONSOCKET_HPP
# define CONNECTIONSOCKET_HPP

# include <iostream>
# include <string>

# include "./SimpleSocket.hpp"
# include "./../../global.hpp"
class AcceptingSocket
{
	public:
		AcceptingSocket(void);
		~AcceptingSocket();

		int	startAccepting(int socket);
		int	disconnect();

		int			getClientSocket(void);
		sockaddr_in	getClientAddress(void);


	private:
		int			_clientSocket;
		sockaddr_in	_clientAddress;

};

#endif /* ************************************************ AcceptingSocket_H */
