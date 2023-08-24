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


if __name__ == "__main__":
	test ("Default [GET]",
			"tests/methods/GET/00_default.conf",
			test_default)


