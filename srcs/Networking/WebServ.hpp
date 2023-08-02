/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 18:34:08 by smodesto          #+#    #+#             */
/*   Updated: 2023/06/25 19:01:04 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEB_SERV_HPP
#define WEB_SERV_HPP


# include <string.h>
# include <unistd.h>
# include "./SimpleServer.hpp"
# include "../httpMessages/Request/RequestParser.hpp"
namespace FT
{
	class WebServ: public SimpleServer
	{
		public:

			WebServ();
			~WebServ();

			void launch(void);

		private:
			int			_newSocket;

			void	_GetRequest(int _socketFd);
			void	accepter();
			void	handler();
			void	responder();
	};
}



#endif /* ******************************************************* WebServ_H */
