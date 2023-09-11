#!/bin/bash

import sys
import os
import select
from glob import glob


def make_line(tag, content):
    return f"<{tag}>{content}</{tag}>"


print('<html>')
print('<head>')
print('<title>CGI test</title>')
print('</head>')
print('<body>')

if select.select([sys.stdin, ], [], [], 0.0)[0]:
    file = input()
    if file == "":
        print(make_line("h1", "Empty query"))
    else:
        if glob(f"{os.environ['DOCUMENT_ROOT']}/**/{file}", recursive=True):
            print(make_line("h1", "The file exist!"))
        else:
            print(make_line("h1", "There is no such a thing...."))

else:
    print(make_line("h1", "Empty query"))

print('</body>')
print('</html>')
