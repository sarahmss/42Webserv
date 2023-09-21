#!/bin/bash

import sys
import os
import select
from glob import glob


def make_line(tag, content):
    return f"<{tag}>{content}</{tag}>"


def check_exist_file(file):
    if glob(f"{os.environ['DOCUMENT_ROOT']}/**/{file}", recursive=True):
        print(make_line("h2", "The file exist!"))
    else:
        print(make_line("h2", "There is no such a thing...."))


print('<html>')
print('<head>')
print('<title>CGI test</title>')
print('</head>')
print('<body>')

if (os.environ['REQUEST_METHOD'] == "GET"):
    if select.select([sys.stdin, ], [], [], 0.0)[0]:
        file = input()
        if file == "":
            print(make_line("h1", "Empty query"))
        else:
            make_line("h1", "Using the req body to search! :D")
            check_exist_file(file)

elif (os.environ['REQUEST_METHOD'] == "POST"):
    file = os.environ["QUERY_STRING"]
    if (file == ""):
        make_line("h1", "Empty query")
    else:
        make_line("h1", "Using the query string to search! :D")
        check_exist_file(file)

else:
    make_line("h1", "MEH!!!! >:(")

print('</body>')
print('</html>')
