import sys
sys.path.append('./tests')
import methods

def test_single_server():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_stts_code(response, 200)

if __name__ == "__main__":
	print ("=" * 80)
	methods.test ("Basic index",
			"./tests/directives/redirection/00_redir.conf",
			test_single_server)

