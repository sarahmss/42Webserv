# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    conf_file.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smodesto <smodesto@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/20 16:36:46 by smodesto          #+#    #+#              #
#    Updated: 2023/07/20 17:55:57 by smodesto         ###   ########.fr        #
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

	print(test_name, end="")
	try:
		assert expected_error in stdout, f"❌ Erro esperado não encontrado na saída: {stdout}"
	except AssertionError as e:
		print(e)
	print ("✔️")

if __name__ == "__main__":
	test(	"void_server_block",
			"./tests/conf_file/void_server_block.conf",
			"Error: Failed setting server [directives]\n")

