#!/usr/bin/python3.8

import datetime

print('<html>')
print('<head>')
print('<title>CGI test</title>')
print('</head>')
print('<body>')
print('<h2>A simple CGI script</h2>')
print(f"<p>Access date: {datetime.datetime.now()}</p>")
print('</body>')
print('</html>')
