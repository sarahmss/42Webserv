import sys
sys.path.append('./tests')
import methods

def test():
	URL = "http://localhost:8080"
	response = methods.post(URL, "Testing POST...")
	methods.check_stts_code(response)

if __name__ == "__main__":
	test()
