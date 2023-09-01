import sys
sys.path.append('./tests')
import methods

def test_default():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_stts_code(response)

if __name__ == "__main__":
	methods.test ("Default GET [200:OK]",
			"tests/methods/GET/00_default.conf",
			test_default)


