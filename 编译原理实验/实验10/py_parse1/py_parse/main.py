from translation import *

with open('binary_search.py','r') as f:
    data = f.read()
    Parse = trans_py(data,print_node=False)

with open('select_sort.py','r') as f:
    data = f.read()
    Parse = trans_py(data,print_node=False)

