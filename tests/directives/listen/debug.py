import sys
sys.path.append('./tests')
import methods

def test_single_server():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_stts_code(response)
	print()


if __name__ == "__main__":
	test_single_server()
