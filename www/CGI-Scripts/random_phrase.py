#!/usr/bin/env python

from random import randint

random_phrase = ["Damn you enraged whale!",
                 "Thou shalt not pass!",
                 "Harry Potter is overrated...",
                 "Baking bread it's not hard!",
                 "Angry cats will dominate the world!",
                 "I'm only a human afterall, don't put your blame on me....",
                 "Gotcha!"]

print('<html>')
print('<head>')
print('<title>Random Phrase</title>')
print('</head>')
print('<body>')
print('<h2>Get your suprise sentence!</h2>')
print(f"<p>Your phrase: {random_phrase[randint(0, len(random_phrase) - 1)]}</p>")
print('</body>')
print('</html>')
