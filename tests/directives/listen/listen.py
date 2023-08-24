import sys
import time
sys.path.append('./tests')
import methods
import subprocess

def start_webserv(infile):
	global web_server_process
	web_server_process = subprocess.Popen(["sudo", "./webserv", infile])

def test(test_name, infile, test_func):
	start_webserv(infile)
	time.sleep(2)
	print (test_name, end="")
	test_func()
	subprocess.run(["pkill", "-SIGINT", "webserv"])


def test_default():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	assert response.status_code == 200

def test_single_server():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	assert response.status_code == 200

def test_2_multservers():
	URL_1 = "http://localhost:9000"
	URL_2 = "http://localhost:9001"
	response = methods.get(URL_1)
	assert response.status_code == 200
	response = methods.get(URL_2)
	assert response.status_code == 200

def test_3_multservers():
	URL_1 = "http://localhost:9000"
	URL_2 = "http://localhost:9001"
	URL_3 = "http://localhost:9002"
	response = methods.get(URL_1)
	assert response.status_code == 200
	response = methods.get(URL_2)
	assert response.status_code == 200
	response = methods.get(URL_3)
	assert response.status_code == 200

if __name__ == "__main__":
	test ("Single Server [900]",
			"tests/directives/listen/01_single_server.conf",
			test_single_server)
	test ("Default [8080]",
		"tests/directives/listen/00_default.conf",
		test_default)
	test("2 Mult servers [9000, 9001]",
			"tests/directives/listen/02_multservers.conf",
			test_2_multservers)
	test("3 Mult servers [9000, 9001, 9002]",
			"tests/directives/listen/03_multservers.conf",
			test_3_multservers)

