import sys
sys.path.append('./tests')
import methods

INDEX = "Webserv directives [allowed_methods]"

def test_all_allowed_methods():
	URL = "http://localhost:8080/"
	response = methods.get(URL)
	#methods.check_text(response, INDEX)
	methods.check_stts_code(response)
	# response = methods.post(URL, "text to post")
	# assert INDEX in response.text
	# assert response.status_code == 200
	# response = methods.delete(URL)
	# assert INDEX in response.text
	# assert response.status_code == 200

def test_location_diff():
	URL = "http://localhost:8080/"
	response = methods.get(URL)
	assert response.status_code == 200


def test_basic_invalid_method():
	URL = "http://localhost:8080/"
	response = methods.get(URL)
	assert response.status_code == 405

"""
	# sending POST where we only want to accept GET and DELETE
"""
def test_invalid_method():
	URL = "http://localhost:8080/"
	response = methods.post(URL, "text to post")
	assert response.status_code == 200
	assert INDEX in response.text
	URL = "http://localhost:8080/bar"
	response = methods.post(URL, "text to post")
	assert response.status_code == 405

if __name__ == "__main__":
	methods.test ("All allowed: global, location -> [ALL]",
			"tests/directives/allowed_methods/00_all_alowed.conf",
			test_all_allowed_methods())

	# methods.test ("Location diff: global -> [ALL], location -> [POST] ",
	# 		"tests/directives/allowed_methods/01_location_diff.conf",
	# 		test_all_allowed_methods())

	# methods.test ("Invalid methods: global -> [NONE], location -> [POST] ",
	# 		"tests/directives/allowed_methods/02_invalid_method.conf",
	# 		test_all_allowed_methods())

	# methods.test ("Invalid methods: global -> [NONE], location -> [POST] ",
	# 		"tests/directives/allowed_methods/03_invalid_method.conf",
	# 		test_all_allowed_methods())


