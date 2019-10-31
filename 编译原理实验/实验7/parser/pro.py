import re




p = r'[A-Za-z]+|[a-zA-Z_][a-zA-Z0-9_]*|[A-Z]*\.[A-Z]$'

p= re.compile(p)

print(p.match('sad_').group())