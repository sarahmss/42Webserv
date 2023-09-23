import sys
sys.path.append('./tests')
import methods

def test_empty_size():
	URL = "http://localhost:8080"
	file_path = "./tests/directives/client_body_size/files/1Mb.txt"

	with open(file_path, 'r') as file:
		larg_text = file.read()

	response = methods.post(URL, larg_text)
	methods.check_stts_code(response)


def test_greater_than_max_size():
	URL = "http://localhost:8080"
	file_path = "./tests/directives/client_body_size/files/1Mb.txt"

	with open(file_path, 'r') as file:
		larg_text = file.read()

	response = methods.post(URL, larg_text)
	methods.check_stts_code(response, 413)

if __name__ == "__main__":
	methods.test ("Default client_max_body_size Sending [1 Mb] -> To [1MB]",
			"tests/directives/client_body_size/00_empty_size.conf",
			test_empty_size)
	methods.test ("client_max_body_size: Sending [1 Mb] -> To [1KB]",
			"tests/directives/client_body_size/01_max_size_1K.conf",
			test_greater_than_max_size)
