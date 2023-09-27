
import requests as req


def send_post(uri: str, data: dict):
    return req.post(uri, data)


print(send_post("http://127.0.0.1:8080/py-post/query.py",
                {'query': 'index.html'}))
