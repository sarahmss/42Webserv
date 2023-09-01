import requests
import subprocess
import signal
import time
import os

def get_log_file(infile):
	log_file_name = os.path.splitext(infile)[0] + ".log"
	log_file_path = os.path.join("logs", log_file_name)
	os.makedirs("logs", exist_ok=True)
	return (log_file_path)

def start_webserv(infile):
	global web_server_process
	log_file_path = get_log_file(infile)
	os.makedirs(os.path.dirname(log_file_path), exist_ok=True)
	with open(log_file_path, 'w') as log_file:
		web_server_process = subprocess.Popen(["sudo", "./webserv", infile],
												stdout=log_file,
												stderr=log_file)

def test(test_name, infile, test_func):
	print (test_name, end="")
	start_webserv(infile)
	time.sleep(2)
	if (test_func() == True):
		print(" -> ✔️")
	else:
		print("-> ❌ Error []")
	web_server_process.send_signal(signal.SIGINT)


""""
	@brief: Makes a GET request and returns response
"""
def get(URL):
	try:
		response = requests.get(URL)
		return response
	except:
		print(" -> ❌ Error [request.get] " + URL)
		exit(1)

""""
	@brief: Makes a POST request and returns response
		@params:
			body: data to post
"""
def post(URL, body):
	try:
		response = requests.post(URL, data=body)
		return response
	except:
		print("-> ❌ Error [request.post] " + URL)
		exit(1)

""""
	@brief: Makes a POST chuncked request and returns response
		@params:
			body: data to post
"""
def chunkedPost(URL, body):
	try:
		response = requests.post(URL, data=body, headers={"Transfer-Encoding": "chunked"})
		return response
	except:
		print("-> ❌ Error [request.post] " + URL)
		exit(1)
