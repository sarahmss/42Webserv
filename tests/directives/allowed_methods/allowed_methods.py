import sys
sys.path.append('./tests')
import methods

def test_post_not_allowed():
	URL = "http://localhost:9000"
	response = methods.post(URL, "Testing POST...")
	methods.check_stts_code(response, 405)

def test_delete_not_allowed():
	URL = "http://localhost:9000"
	response = methods.delete(URL)
	methods.check_stts_code(response, 405)

def test_unknown_method():
	URL = "http://localhost:9000"
	response = methods.head(URL)
	methods.check_stts_code(response, 501)

def test_post_allowed():
	URL = "http://localhost:9000"
	response = methods.post(URL, "Testing POST...")
	methods.check_stts_code(response)

def test_delete_allowed():
	URL = "http://localhost:9000"
	response = methods.delete(URL)
	methods.check_stts_code(response)


if __name__ == "__main__":
	print ("=" * 40, "Alowed methods", "=" * 40)
	methods.test ("Testing POST not allowed",
			"tests/directives/allowed_methods/00_only_get.conf",
			test_post_not_allowed)
	methods.test ("Testing DELETE not allowed",
			"tests/directives/allowed_methods/00_only_get.conf",
			test_delete_not_allowed)
	methods.test ("Testing HEAD not implemented",
			"tests/directives/allowed_methods/00_only_get.conf",
			test_unknown_method)
	methods.test ("Testing POST allowed",
			"./tests/directives/allowed_methods/01_all_allowed.conf",
			test_post_allowed)
	methods.test ("Testing DELETE allowed",
			"./tests/directives/allowed_methods/01_all_allowed.conf",
			test_delete_allowed)
