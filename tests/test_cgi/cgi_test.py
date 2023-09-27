
import requests as req


def send_post(uri: str, data: dict):
    return req.post(uri, data)


def send_get(uri: str):
    return req.get(uri)


def check_status_code(status, expected: int):
    try:
        assert status.status_code == expected
        print("Success")
    except AssertionError:
        print("Failure")


if __name__ == "__main__":
    # Post section
    check_status_code(send_post("http://127.0.0.1:8080/py-post/query.py",
                                {'query': 'index.html'}), 200)

    check_status_code(send_post("http://127.0.0.1:8080/py-post/something.py",
                                {'query': 'index.html'}), 404)

    # Get section
    check_status_code(send_get("http://127.0.0.1:8080/py/hello.py"), 200)

    check_status_code(send_get("http://127.0.0.1:8080/py/query.py?query=index.html"), 200)

    check_status_code(send_get("http://127.0.0.1:8080/py/query.py?query=index.html&query2=something.html"), 200)

    check_status_code(send_get("http://127.0.0.1:8080/py/random_phrase.py"), 200)

    check_status_code(send_get("http://127.0.0.1:8080/py/not_found"), 404)
