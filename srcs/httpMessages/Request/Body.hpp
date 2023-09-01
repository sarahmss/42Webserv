/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:58:42 by smodesto          #+#    #+#             */
/*   Updated: 2023/09/01 16:05:05 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BODY_HPP
# define BODY_HPP

# include "../Utils.hpp"
# define EMPTYBODY -1
# define CHUNKED 1
# define UNCHUNKED 2

	class Body
	{
		public:
			Body(int socketFd, HeadersType headers);
			~Body();

			int			parseBody();
			std::string	getBody(void);
			std::string	getFileName(void);
			int			getContentLength(void);

			bool		IsMultipartForm();
		private:
			int			_socketFd;
			HeadersType	_headers;
			std::string	_body;
			std::string	_fileName;
			std::string	_boundary;
			int			_ContentLenght;

			int		_HandleChunkedBody();
			size_t		_getChunkSize();
			size_t		_convertChunkSize(std::string chunkSize);
			int			_ReadMessageBody();
			void		_getBodyMessage(std::string &Body);
			void		_ClearBoundary(std::string &Body);
			void		_ClearHeader(std::string &Body);
			void		_getFileName(std::string header);
			void		_getBoundary(std::string header);

	};
#endif /* ************************************************************ BODY_H */
