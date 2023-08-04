/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/03 22:20:12 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include "../../Settings/Parser.hpp"
# include "./RequestParser.hpp"

namespace FT {
	class Request
	{
		public:
			Request(int socketFd);
			~Request();

			void	launch(void);
		private:
			int				_socketFd;
			RequestParser	_requestParser;
			std::string		_serverName;
			std::string		_uri;
			ServerVecType	_serversConfs;

			void			_runRequest(void);
			void			_chooseServer(void);


	};
}

#endif /* *************************************************** Request_H */
