#!/usr/bin/env python

import os
import sys
from glob import glob


def make_line(tag, content):
    return f"<{tag}>{content}</{tag}>"


def check_exist_file(file):
    if glob(f"{os.environ['DOCUMENT_ROOT']}/**/{file}", recursive=True):
        print(make_line("h2", f"{file} - The file exist!"))
    else:
        print(make_line("h2", f"{file} - There is no such a thing...."))


def parse_query(query_string):
    parsed = {}
    split_query = query_string.split("&")
    for query in split_query:
        key_value = query.split('=')
        if len(key_value) == 1:
            sys.exit(1)
        parsed[key_value[0]] = key_value[1]
    return parsed


print('<html>')
print('<head>')
print('<title>CGI test</title>')
print('</head>')
print('<body>')

if (os.environ['REQUEST_METHOD'] == "POST"):
    query_string = os.environ['REQUEST_BODY']
    if query_string == "":
        print(make_line("h1", "Empty query"))
    else:
        print(make_line("h1", "POST - Using the req body to search! :D"))
        query = parse_query(query_string)
        for key in query:
            check_exist_file(query[key])

elif (os.environ['REQUEST_METHOD'] == "GET"):
    query_string = os.environ["QUERY_STRING"]
    if (query_string == ""):
        print(make_line("h1", "Empty query"))
    else:
        print(make_line("h1", "Get - Using the query string to search! :D"))
        query = parse_query(query_string)
        for key in query:
            check_exist_file(query[key])

else:
    print(make_line("h1", "MEH!!!! >:("))

print('</body>')
print('</html>')
