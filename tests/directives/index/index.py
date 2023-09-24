import sys
sys.path.append('./tests')
import methods

def test_single_index():
	URL = "http://localhost:8080"
	response = methods.get(URL)
	methods.check_html(response.text, "Testing index...")

def test_mult_index():
	URL1 = "http://localhost:8080"
	URL2 = "http://localhost:9000"
	URL3 = "http://localhost:4444"

	response = methods.get(URL1)
	methods.check_html(response.text, "Testing index [1]...")
	response = methods.get(URL2)
	methods.check_html(response.text, "Testing index [2]...")
	response = methods.get(URL3)
	methods.check_html(response.text, "Testing index [3]...")


if __name__ == "__main__":
	print ("=" * 80)
	methods.test ("Basic index",
			"./tests/directives/index/00_index.conf",
			test_single_index)
	methods.test ("Mult index",
			"./tests/directives/index/01_mult_index.conf",
			test_mult_index)
