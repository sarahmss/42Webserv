import http.client

def chunk_data(data, chunk_size):
	dl = len(data)
	ret = ""
	for i in range(dl // chunk_size):
		ret += "%s\r\n" % (hex(chunk_size)[2:])
		ret += "%s\r\n\r\n" % (data[i * chunk_size : (i + 1) * chunk_size])

	if len(data) % chunk_size != 0:
		ret += "%s\r\n" % (hex(len(data) % chunk_size)[2:])
		ret += "%s\r\n" % (data[-(len(data) % chunk_size):])

	ret += "\r\n\r\n"
	return ret


def set_headers(connection: http.client.HTTPConnection):
	url = "/uploads/"
	connection.putrequest("POST", url)
	connection.putheader("Transfer-Encoding", "chunked")
	connection.putheader("Filename", "chunkedPost.txt")
	connection.putheader("Content-Type", "multipart/form-data")
	connection.endheaders()


def send_chunked_request():
	body_chunk = "Chunked body\n"
	body = body_chunk * 42
	host = "localhost:9000"

	print ("Sending Chunked Body...")
	connection = http.client.HTTPConnection(host)
	set_headers(connection)
	connection.send(chunk_data(body, len(body_chunk)).encode("utf-8"))
	print(body)
	response = connection.getresponse()
	print ("Receiving response...\n ", response.msg)
	print(response.status, response.reason)
	connection.close()


def main():
	send_chunked_request()


if __name__ == "__main__":
    main()
