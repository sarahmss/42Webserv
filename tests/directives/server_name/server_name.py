import sys
sys.path.append('./tests')
import methods

def test_empty_name():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_text(response.headers['Server'], "")

def test_single_name():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_text(response.headers['Server'], "www.webserv.com ")

def test_mult_name():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_text(response.headers['Server'], "webserv webserv.br webserv.fr ")

if __name__ == "__main__":
	print ("=" * 40, "Misconfig", "=" * 40)
	methods.test ("Testing server empty name []",
			"tests/directives/server_name/00_empty_name.conf",
			test_empty_name)
	methods.test ("Testing server single name [www.webserv.com]",
			"tests/directives/server_name/01_single_name.conf",
			test_single_name)
	methods.test ("Testing server mult name [webserv webserv.br webserv.fr]",
			"tests/directives/server_name/02_mult_name.conf",
			test_mult_name)
