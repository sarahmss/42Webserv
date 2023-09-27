import sys
sys.path.append('./tests')
import methods

def test_empty_size():
	URL = "http://localhost:8080"
	file_path = "./tests/directives/client_body_size/files/1Mb.txt"

	with open(file_path, 'r') as file:
		text = file.read()

	response = methods.post(URL, text)
	methods.check_stts_code(response)

def test_greater_than_max_size():
	URL = "http://localhost:8080"
	file_path = "./tests/directives/client_body_size/files/1Mb.txt"

	with open(file_path, 'r') as file:
		text = file.read()

	response = methods.post(URL, text)
	methods.check_stts_code(response, 413)

def test_less_than_max_size():
	URL = "http://localhost:8080"
	file_path = "./tests/directives/client_body_size/files/1Kb.txt"

	with open(file_path, 'r') as file:
		text = file.read()

	response = methods.post(URL, text)
	methods.check_stts_code(response, 200)


if __name__ == "__main__":
	print ("=" * 80)
	methods.test ("Default client_max_body_size Sending [1 Mb] -> To [1 Mb]",
			"tests/directives/client_body_size/00_empty_size.conf",
			test_empty_size)
	methods.test ("Global client_max_body_size: Sending [1 Mb] -> To [1 Kb]",
			"tests/directives/client_body_size/01_max_size_1K.conf",
			test_greater_than_max_size)
	methods.test ("Location client_max_body_size: Sending [1 Mb] -> To [1 Kb]",
			"tests/directives/client_body_size/02_max_size_1K_location.conf",
			test_greater_than_max_size)
	methods.test ("Global client_max_body_size: Sending [1 Kb] -> To [1 Mb]",
			"tests/directives/client_body_size/03_max_size_1M.conf",
			test_less_than_max_size)
	methods.test ("Location client_max_body_size: Sending [1 Kb] -> To [1 Mb]",
			"tests/directives/client_body_size/04_max_size_1M_location.conf",
			test_less_than_max_size)
