/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:27:22 by smodesto          #+#    #+#             */
/*   Updated: 2023/07/31 19:30:33 by smodesto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./srcs/Settings/Parser.hpp"
# include "./srcs/Networking/WebServ.hpp"

std::string	SetConfigurationFile(int argc, char *argv[])
{
	if (argc > 2)
	{
		std::cout << "./webserv [configuration_file_path]" << std::endl;
		exit(EINVAL);
	}
	if (argc == 1)
	{
		std::cout << "Not given conf file, launching default..." << std::endl;
		return ("./conf/webserv.conf");
	}
	return(argv[1]);
}

void	ParseConfigurationFile(FT::Parser &parser, std::string filename)
{
	try {
		parser.launch(filename);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		exit(EBADF);
	}
}

int main(int argc, char **argv)
{
	std::string	filename;
	FT::Parser	parser;
	FT::WebServ	WebServ;

	filename = SetConfigurationFile(argc, argv);
	ParseConfigurationFile(parser, filename);
	std::cout << parser;
	WebServ.launch();
}
