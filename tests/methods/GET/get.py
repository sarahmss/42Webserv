import sys
sys.path.append('./tests')
import methods

def test_default():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	return (response.status_code == 200)

if __name__ == "__main__":
	methods.test ("Default [GET]",
			"tests/methods/GET/00_default.conf",
			test_default)


