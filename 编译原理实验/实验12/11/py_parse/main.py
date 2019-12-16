from translation import *


with open('stu.py','r') as f:
    data = f.read()
    Parse = Tran()
    Parse.trans_py(data,print_node=True)


