/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:58:42 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/02 00:41:22 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BODY_HPP
# define BODY_HPP

# include "../Utils.hpp"

namespace FT {
	class Body
	{
		public:
			Body(int socketFd, HeadersType headers);
			~Body();

			int			parseBody();
			std::string	GetBody(void);
			std::string	GetFileName(void);


		private:
			int			_socketFd;
			HeadersType	_headers;
			std::string	_body;
			std::string	_fileName;

			void		_HandleChunckedBody();
			ssize_t		_getChunckSize();
			void		_ReadMessageBody();
			void		_GetBodyMessage(std::string &Body);
			bool		_IsMultipartFormData();
			void		_ClearFooter(std::string &Body);
			void		_ClearHeader(std::string &Body);
			void		_GetFileName(std::string header);

	};
}
#endif /* ************************************************************ BODY_H */
