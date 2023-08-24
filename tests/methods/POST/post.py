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

def test_default_post():
	URL = "http://localhost:8080"
	response = methods.post(URL, "This is a simple text body.")
	assert response.status_code == 201

def test_chuncked_post():
	URL = "http://localhost:8080"
	response = methods.chunkedPost(URL, "This is a simple text body.")
	assert response.status_code == 201


if __name__ == "__main__":
	test ("Default Post [201 : Created]",
			"tests/methods/POST/00_default.conf",
			test_default_post)
	test ("Chunked Post [201 : Created]",
			"tests/methods/POST/00_default.conf",
			test_default_post)


