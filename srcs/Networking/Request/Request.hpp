/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:09:32 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/25 23:09:33 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>

class Request
{

	public:

		Request();
		Request( Request const & src );
		~Request();

		Request &		operator=( Request const & rhs );

	private:

};

std::ostream &			operator<<( std::ostream & o, Request const & i );

#endif /* *************************************************** Request_H */
