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

def check_stts_code(response, code=200):
	try:
		assert response.status_code == code, f"-> ❌ Error sttsCode [{response.status_code}]"
		print(f" -> ✔️  sttsCode [{response.status_code}]")
	except AssertionError as e:
		print(e)

def check_text(response, text):
	try:
		assert response.text == text, f"-> ❌ Error text [{response.text}]"
		print(f" -> ✔️  text [{response.text}]")
	except AssertionError as e:
		print(e)


def test(test_name, infile, test_func):
	print (test_name, end="")
	start_webserv(infile)
	time.sleep(2)
	test_func()
	web_server_process.send_signal(signal.SIGINT)


""""
	@brief: Makes a GET request and returns response
"""
def get(URL):
	try:
		response = requests.get(URL)
		return response
	except AssertionError as e:
		print("-> ❌ Error request.get " + URL + f"[{e}]")
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
	except AssertionError as e:
		print("-> ❌ Error request.post " + URL + f"[{e}]")
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
	except AssertionError as e:
		print("-> ❌ Error request.post " + URL + f"[{e}]")
		exit(1)
