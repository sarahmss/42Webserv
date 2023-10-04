#!/usr/bin/python3.8

import os


print('<html>')
print('<head>')
print('<title>I can see you</title>')
print('</head>')
print('<body>')
print('<h2>A simple CGI script</h2>')
print(f"<p>Sir your ip should be: {os.environ['REMOTE_ADDR']}</p>")
print(f"<p>And the port should be: {os.environ['REMOTE_PORT']}</p>")
print("<img src='https://i.imgflip.com/6u6cx2.jpg' width='400px'>")
print('</body>')
print('</html>')
