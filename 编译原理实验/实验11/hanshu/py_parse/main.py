from translation import *


with open('quick_sort.py','r') as f:
    data = f.read()
    Parse = Tran()
    Parse.trans_py(data,print_node=False)

