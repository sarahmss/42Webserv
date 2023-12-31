/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:35:47 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/31 13:45:14 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLLHANDLER_HPP
# define POLLHANDLER_HPP

#include <string.h>
#include <unistd.h>
# include <iostream>
# include <string>
# include <sys/epoll.h>
# include <fcntl.h>
# include "../Networking/SimpleServer.hpp"

# define MAX_EVENTS 500

typedef struct epoll_event epollEventType;

class PollHandler
{
	public:
		PollHandler(size_t eventsMax);
		~PollHandler(void);

		int		add(int fd, epoll_data_t data, uint32_t events);
		int		modify(int fd, epoll_data_t data, uint32_t newEvents);
		int		remove(int fd);
		int		wait(int timeout);

		epoll_data_t	ChannelToData(t_channel *channel);
		epollEventType	*getEvents(void);
	private:
		epollEventType	*_interestList;
		int				_epollFd;
		size_t			_eventsMax;
};


#endif /* ***************************************************** POLLHANDLER_H */
