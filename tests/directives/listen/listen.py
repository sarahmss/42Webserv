import sys
sys.path.append('./tests')
import methods

def test_single_server():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_stts_code(response, 404)

def test_2_multservers():
	URL_1 = "http://localhost:9000"
	URL_2 = "http://localhost:9001"
	response = methods.get(URL_1)
	methods.check_stts_code(response, 404)
	response = methods.get(URL_2)
	methods.check_stts_code(response, 404)

def test_3_multservers():
	URL_1 = "http://localhost:9000"
	URL_2 = "http://localhost:9001"
	URL_3 = "http://localhost:9002"
	response = methods.get(URL_1)
	methods.check_stts_code(response, 404)
	response = methods.get(URL_2)
	methods.check_stts_code(response, 404)
	response = methods.get(URL_3)
	methods.check_stts_code(response, 404)

if __name__ == "__main__":
	print ("=" * 40, "Listen", "=" * 40)
	methods.test ("Single Server [9000]",
			"tests/directives/listen/01_single_server.conf",
			test_single_server)
	methods.test("2 Mult servers [9000, 9001]",
			"tests/directives/listen/02_multservers.conf",
			test_2_multservers)
	methods.test("3 Mult servers [9000, 9001, 9002]",
			"tests/directives/listen/03_multservers.conf",
			test_3_multservers)

