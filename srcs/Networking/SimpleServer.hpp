/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 19:35:51 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/31 14:53:57 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESERVER_HPP
# define SIMPLESERVER_HPP

# include <iostream>
# include <string>
# include <string.h>
# include <unistd.h>
#include "./Sockets/Sockets.hpp"
# include "../httpMessages/Request/RequestParser.hpp"
# include "../httpMessages/Request/Handler.hpp"
typedef struct s_channel
{
	void	*ptr;

	enum t_channelType
	{
		CHANNEL_SOCKET,
		CHANNEL_CONNECTION
	} type;

}	t_channel;

class SimpleServer
{
	public:
		SimpleServer(ServerConf Confs, const int port, int backlog);
		~SimpleServer();

		void				init(void);

		ListeningSocket	*getListeningSocket(void);
		ServerConf		getConf(void);
		sockaddr_in		getAddress(void);
		int				getSocket(void);
		int				getPort(void);
		int				getBacklog(void);

	private:
		ListeningSocket			*_socket;
		ServerConf				_confs;
		int						_port;
		int						_backlog;
};

#endif /* **************************************************** SIMPLESERVER_H */
