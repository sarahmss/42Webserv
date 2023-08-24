import sys
sys.path.append('./tests')
import methods


def test_default_post():
	URL = "http://localhost:8080"
	response = methods.post(URL, "This is a simple text body.")
	return (response.status_code == 201)

def test_chuncked_post():
	URL = "http://localhost:8080"
	response = methods.chunkedPost(URL, "This is a simple text body.")
	return (response.status_code == 201)


if __name__ == "__main__":
	methods.test ("Default Post [201 : Created]",
			"tests/methods/POST/00_default.conf",
			test_default_post)
	methods.test ("Chunked Post [201 : Created]",
			"tests/methods/POST/00_default.conf",
			test_default_post)


