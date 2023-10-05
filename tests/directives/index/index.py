import sys
sys.path.append('./tests')
import methods

def test_single_index():
	URL = "http://localhost:9000"
	response = methods.get(URL)
	methods.check_html(response.text, "Testing index...")

def test_mult_index():
	URL1 = "http://localhost:9000"
	URL2 = "http://localhost:9001"
	URL3 = "http://localhost:9002"

	response = methods.get(URL1)
	methods.check_html(response.text, "Testing index [1]...")
	response = methods.get(URL2)
	methods.check_html(response.text, "Testing index [2]...")
	response = methods.get(URL3)
	methods.check_html(response.text, "Testing index [3]...")


if __name__ == "__main__":
	print ("=" * 40, "Index", "=" * 40)
	methods.test ("Basic index",
			"./tests/directives/index/00_index.conf",
			test_single_index)
	methods.test ("Mult index",
			"./tests/directives/index/01_mult_index.conf",
			test_mult_index)
