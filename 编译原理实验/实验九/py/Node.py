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
    def print_node_val(self):
        if self._data=='[PRINT]':
            for child in range(len(self._children)):
                if child!=len(self._children)-1:
                    if self._children[child].getVal()!=None:
                        print(self._children[child].getVal(),end=' ')
                    else:
                        print(VaribleTable[self._children[child].getData()],end=' ')
                else:
                    if self._children[child].getVal()!=None:
                        print(self._children[child].getVal())
                    else:
                        print(VaribleTable[self._children[child].getData()])
        else:
            for i in self._children:
                i.print_node_val()

