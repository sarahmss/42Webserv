import sys
sys.path.append('./tests')
import methods

def test_autoindex_on():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_html(response.text, "subfolder")
	methods.check_html(response.text, "file1")
	methods.check_html(response.text, "file2")

def test_autoindex_off():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_stts_code(response, 404)

def test_autoindex_on_subfolder():
	URL1 = "http://localhost:8080"
	URL2 = "http://localhost:8080/subfolder"

	response = methods.get(URL1)
	methods.check_stts_code(response, 404)
	response = methods.get(URL2)
	methods.check_html(response.text, "subfile1")
	methods.check_html(response.text, "subfile2")


if __name__ == "__main__":
	print ("=" * 80)
	methods.test ("AutoIndex on",
			"./tests/directives/autoindex/00_autoindex_on.conf",
			test_autoindex_on)
	methods.test ("Autoindex off",
			"./tests/directives/autoindex/01_autoindex_off.conf",
			test_autoindex_off)
	methods.test ("Autoindex on in subfolder",
			"./tests/directives/autoindex/02_autoindex_on_subfolder.conf",
			test_autoindex_on_subfolder)
