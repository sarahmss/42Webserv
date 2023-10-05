import sys
sys.path.append('./tests')
import methods

def test_inavlid_redirection():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_stts_code(response, 404)

def test_google_redirection():
	URL = "http://localhost:9000/"
	response = methods.get(URL)
	redirect = response.history[0]
	methods.check_text(redirect.url, URL)
	methods.check_stts_code(redirect, 301)
	redirect = response.history[1]
	methods.check_text(redirect.url, "https://google.com")
	methods.check_stts_code(redirect, 301)
	methods.check_stts_code(response)


def test_valid_redirection():
	URL = "http://localhost:9000/www"
	response = methods.get(URL)
	methods.check_html(response.text, "Redirection ok...")
	redirect = response.history[0]
	methods.check_text(redirect.url, URL)
	methods.check_stts_code(redirect, 301)
	methods.check_text(response.url, "http://localhost:9000/redir")


if __name__ == "__main__":
	print ("=" * 40, "Redirection", "=" * 40)
	methods.test ("Redirecting to non exist",
			"./tests/directives/redirection/00_invalid_redir.conf",
			test_inavlid_redirection)
	methods.test ("Redirecting from www/ to redir/",
			"./tests/directives/redirection/01_redir.conf",
			test_valid_redirection)
	methods.test ("Redirecting from / to https://google.com",
			"./tests/directives/redirection/02_redir_google.conf",
			test_google_redirection)
