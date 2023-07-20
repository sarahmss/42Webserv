# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf_file.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 16:36:46 by smodesto          #+#    #+#              #
#    Updated: 2023/07/20 20:45:39 by smodesto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
		assert expected_error in stdout, f" -> ❌ {stdout}"
	except AssertionError as e:
		print(e)
		wrong = True
	if (wrong == False):
		print(f" -> ✔️  {stdout}", end="")

def test_server_blocks():
	print ("=" * 80)
	test(	"void_server_block",
			"./tests/conf_file/void_server_block.conf",
			"Error: Failed setting server [directives]\n")
	test(	"bad_server_block1",
			"./tests/conf_file/bad_server_block1.conf",
			"Error: Failed setting server block [missing bracket]\n")
	test(	"bad_server_block2",
			"./tests/conf_file/bad_server_block2.conf",
			"Error: Failed setting server block\n")
	test(	"bad_server_block3",
			"./tests/conf_file/bad_server_block3.conf",
			"Error: Failed setting server block\n")
	test(	"bad_server_block4",
			"./tests/conf_file/bad_server_block4.conf",
			"Error: Failed setting server block\n")

def test_empty_blocks():
	print ("=" * 80)
	test(	"empty0",
			"./tests/conf_file/empty0.conf",
			"Error: No \"events\" section in configuration\n")
	test(	"empty1",
			"./tests/conf_file/empty1.conf",
			"Error: No \"events\" section in configuration\n")
	test(	"empty2",
			"./tests/conf_file/empty2.conf",
			"Error: No \"events\" section in configuration\n")
	test(	"empty3",
			"./tests/conf_file/empty3.conf",
			"Error: No \"events\" section in configuration\n")
	test(	"empty4",
			"./tests/conf_file/empty4.conf",
			"Error: Failed setting server block\n")

if __name__ == "__main__":
	test_server_blocks()
	test_empty_blocks()

