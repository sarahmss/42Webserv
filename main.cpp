/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- <jinacio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:27:22 by smodesto          #+#    #+#             */
/*   Updated: 2023/08/29 21:28:14 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./srcs/Settings/Parser.hpp"
# include "./srcs/Networking/WebServ.hpp"
# include "./srcs/global.hpp"

void	createFile( void )
{
	std::string pathLog = "/root/webserv/42Webserv/logFile/log.txt";
	const char* filePath = pathLog.c_str();
	
	logFile.open(filePath, std::ios::app);
	if (logFile.is_open())
		sendMessageToLogFile("Log starts | createFile -> Main ", true, 0);
	else
		std::cout << "Log was not created" << std::endl;

	return ;
}

std::string	SetConfigurationFile(int argc, char *argv[])
{
	if (argc > 2)
	{
		std::cout << "./webserv [configuration_file_path]" << std::endl;
		sendMessageToLogFile("Many arguments. Exiting... | SetConfigurationFile -> Main ", false, 0);
		exit(EINVAL);
	}
	if (argc == 1)
	{
		std::cout << "Not given conf file, launching default..." << std::endl;
		sendMessageToLogFile("Lauching default conf file... | SetConfigurationFile -> Main ", true, 0);
		return ("./conf/webserv.conf");
	}
	return(argv[1]);
}

void	ParseConfigurationFile(Parser &parser, std::string filename)
{
	clock_t start = clock();
	try 
	{
		parser.launch(filename);
		clock_t end = clock();
		sendMessageToLogFile("File opened and Parser completed", true,
							 static_cast<double>(end - start) / CLOCKS_PER_SEC);
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		sendMessageToLogFile(e.what(), false, 0);
		exit(EBADF);
	}
}

int main(int argc, char **argv)
{
	std::string	filename;
	Parser	parser;

	createFile();
	filename = SetConfigurationFile(argc, argv);
	ParseConfigurationFile(parser, filename);

	WebServ	WebServ(parser.getServers());
	WebServ.launch();
}
