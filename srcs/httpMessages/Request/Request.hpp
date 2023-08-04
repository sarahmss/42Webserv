/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/04 17:26:48 by smodesto         ###   ########.fr       */
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
			Request(int clientSocket);
			~Request();

			void	launch(void);
		private:
			int				_clientSocket;
			RequestParser	_requestParser;
			std::string		_serverName;
			std::string		_uri;

			void			_runRequest(void);
			void			_chooseServer(void);


	};
}

#endif /* *************************************************** Request_H */
