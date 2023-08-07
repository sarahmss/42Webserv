/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PollHandler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:03:40 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/07 16:18:53 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PollHandler.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

/*
	@brief:
		@param:eventsMax: max number of events to watch
*/
FT::PollHandler::PollHandler(size_t eventsMax) : _eventsMax(eventsMax)
{
	_epollFd = epoll_create(1);
	if (_epollFd == -1)
		throw std::runtime_error("Failed to create epoll");
	_interestList = new epoll_event[_eventsMax];
	memset(_interestList, 0, sizeof(epoll_event) * _eventsMax);
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

FT::PollHandler::~PollHandler()
{
	delete[] _interestList;
	close(_epollFd);
}

/*
** --------------------------------- METHODS ----------------------------------
*/

int FT::PollHandler::add(int fd, epoll_data_t data, uint32_t events)
{
	epollEventType	event;

	event.events = events;
	event.data = data;
	if (epoll_ctl(_epollFd, EPOLL_CTL_ADD, fd, &event) == -1)
	{
		throw std::runtime_error("Failed to add epoll [epoll_ctl]");
		return (-1);
	}
	return (0);
}
int FT::PollHandler::modify(int fd, epoll_data_t data, uint32_t newEvents)
{
	epollEventType event;

	event.events = newEvents;
	event.data = data;
	if (epoll_ctl(_epollFd, EPOLL_CTL_MOD, fd, &event) == -1)
	{
		throw std::runtime_error("Failed to modify epoll [epoll_ctl]");
		return (-1);
	}
	return (0);
}

int FT::PollHandler::remove(int fd)
{
	if (epoll_ctl(_epollFd, EPOLL_CTL_DEL, fd, 0) == -1)
	{
		throw std::runtime_error("Failed to remove epoll [epoll_ctl]");
		return (-1);
	}
	return (0);
}
int FT::PollHandler::wait(int timeout)
{
	int fd = epoll_wait(_epollFd, _interestList, _eventsMax, timeout);
	if (fd == -1)
	{
		throw std::runtime_error("Failed to wait");
		return (-1);
	}
	return (fd);
}

epoll_data_t	FT::PollHandler::ServerToData(SimpleServer *server)
{
	epoll_data_t	eventData;

	eventData.ptr = server;
	return(eventData);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

struct epoll_event *FT::PollHandler::getEvents(void)
{
	return (_interestList);
}
/* ************************************************************************** */
