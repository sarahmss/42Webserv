
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
        print("Failure:")
        print(f"{status.status_code} != {expected}")


if __name__ == "__main__":
    # Post section
    print("POST")
    check_status_code(send_post("http://127.0.0.1:9000/pypost/query.py",
                                {'query': 'index.html'}), 200)

    check_status_code(send_post("http://127.0.0.1:9000/pypost/something.py",
                                {'query': 'index.html'}), 404)

    check_status_code(send_post("http://127.0.0.1:9000/pypost/error.py",
                                {'query': 'index.html'}), 500)

    print("GET:")
    # Get section
    check_status_code(send_get("http://127.0.0.1:9000/py/hello.py"), 200)

    check_status_code(send_get("http://127.0.0.1:9000/py/query.py?query=index.html"), 200)

    check_status_code(send_get("http://127.0.0.1:9000/py/query.py?query=index.html&query2=something.html"), 200)

    check_status_code(send_get("http://127.0.0.1:9000/py/random_phrase.py"), 200)

    check_status_code(send_get("http://127.0.0.1:8080/py/not_found"), 404)

    check_status_code(send_get("http://127.0.0.1:8080/py/error.py"), 500)
