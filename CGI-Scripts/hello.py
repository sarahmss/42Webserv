#!/usr/bin/python

import os

print(os.environ)
print("Content-type:text/html\r\n\r\n")
print('<html>')
print('<head>')
print('<title>CGI test</title>')
print('</head>')
print('<body>')
print('<h2>A simple CGI script</h2>')
print('</body>')
print('</html>')
