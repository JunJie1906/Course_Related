from translation import *

with open('example2.py','r') as f:
    data = f.read()

Parse = trans_py(data)

Parse.print_node_val()


