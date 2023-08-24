import requests

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
