from translation import *


with open('test.py','r') as f:
    data = f.read()
    Parse = Tran()
    Parse.trans_py(data,print_node=False)
