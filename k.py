import requests

# Define the URL where you want to send the data
url = 'http://localhost:8080/py-post/query.py'

# Define the chunk size
chunk_size = 1024  # You can adjust this as needed

# Define a function to generate chunks of data from a file
def chunk_generator(filename):
    with open(filename, 'rb') as file:
        while True:
            chunk = file.read(chunk_size)
            if not chunk:
                break
            yield chunk

# Make a POST request with chunked data
response = requests.post(url, data=chunk_generator('large_file.bin'))

# Check the response
if response.status_code == 200:
    print("Data successfully sent.")
else:
    print(f"Error: {response.status_code} - {response.text}")

print(response.text)
