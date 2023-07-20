# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf_file.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 16:36:46 by smodesto          #+#    #+#              #
#    Updated: 2023/07/20 19:36:33 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# test_server.py
import subprocess

def test(test_name, infile, expected_error):
	process = subprocess.Popen(["./webserv", infile],
								stdout=subprocess.PIPE,
								stderr=subprocess.PIPE,
									text=True)
	stdout, stderr = process.communicate()
	wrong = False

	print(test_name, end="")
	try:
		assert expected_error in stdout, f"❌{stdout}"
	except AssertionError as e:
		print(e)
		wrong = True
	if (wrong == False):
		print ("✔️")

if __name__ == "__main__":
	test(	"void_server_block",
			"./tests/conf_file/void_server_block.conf",
			"Error: Failed setting server [directives]\n")
	test(	"misconfigured1.conf",
			"./tests/conf_file/misconfigured1.conf",
			"Error: Failed setting server block [missing bracket]\n")
