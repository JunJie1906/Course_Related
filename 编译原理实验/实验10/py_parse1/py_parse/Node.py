from VaribleTable import*

class node:
    def __init__(self,data):
        if isinstance(data,node):
            self._val = None
            self._children = data._children
            self._data = data._data
            return
        if data.isdigit():
            self._val = int(data)
        else:
            self._val = None
        self._children = []
        self._data = data
    def add(self,node):
        self._children.append(node)

    def setVal(self,val):
        self._val = val

    def getVal(self):
        return self._val

    def getData(self):
        return self._data

    def getChildren(self):
        return self._children

    def print_node(self, prefix):
        print('  '*prefix,'+',self._data)
        if self._children!=[]:
            for child in self._children:
                child.print_node(prefix+1)

