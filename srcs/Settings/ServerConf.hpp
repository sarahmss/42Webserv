/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 21:15:45 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/10 22:19:11 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CONF_HPP
# define SERVER_CONF_HPP

# include <iostream>
# include <string>
# include <vector>
# include "./Directives/Listen.hpp"
# include "./Directives/Location.hpp"
# include "./Directives/Cgi.hpp"
# include "./Directives/ErrorPages.hpp"

# define ServerNameType		std::vector<std::string>
# define ListenType			Listen
# define LocationType		Location
# define LocationVecType	std::vector<Location>
# define ErrorType			ErrorPages
# define CgiType			Cgi


	class ServerConf
	{
		public:
			ServerConf();
			ServerConf( ServerConf const & src );
			~ServerConf();

			ServerConf &	operator=( ServerConf const & rhs );

			ListenType			getListen(void) const;
			ServerNameType		getServerName(void) const;
			std::string			getRoot(void) const;
			std::string			getErrorPage(std::string code) const;
			ErrorType			getErrorPages(void) const;
			ErrorType			getDefaultErrorPages(void) const;
			CgiType				getCgi(void) const;
			int					getBodySize(void) const;
			LocationVecType		getLocation(void) const;

			void			SetListen(ListenType listen);
			void			SetRoot(std::string root);
			void			SetBodySize(int bodySize);

			void			AddServerName(std::string serverName);
			void			AddLocation(LocationType locationBlock);
			void			AddErrorPage(std::string code, std::string pagePath);
			void			AddCgi(std::string extension,
							std::string programPath);

			bool			IsListenSet(void) const;
			bool			IsServerNameSet(void) const;
			bool			IsRootSet(void) const;
			bool			IsErrorPageSet(std::string code) const;

			std::string		ServerNameToString(void) const;

		private:
			ListenType			_listen;
			ServerNameType		_serverName;
			LocationVecType		_location;
			ErrorType			_errorPages;
			ErrorType			_errorPagesDefault;
			CgiType				_cgi;
			std::string			_root;
			int					_bodySize;

	};

	std::ostream &			operator<<( std::ostream & o, ServerConf const & i );
#endif /* ****************************************************** SERVER_H */
