from py_syn import *
from utils import *
import copy

class Tran:
    def __init__(self):
        self.has_if = False
        self.VariableTable = {}
        self.FunctionTable = {}
        self.RETURN = []
        self.paraList = []

    def trans_py(self,text,print_node = False):
        Parse = yacc.parse(clear_text(text))
        if print_node==True:
            Parse.print_node(0)
            return
        self.dfs(Parse)
        return Parse

    def dfs(self,NODE,argu = False):
        if self.RETURN != []:
            return

        if NODE.getData() == '[IF]':
            self.dfs(NODE._children[0])
            if NODE._children[0].getVal() == True:
                if self.dfs(NODE._children[1]) == False:
                    return False
                self.has_if = False
            else:
                self.has_if = True
            return
        elif NODE.getData() == '[ELSE]':
            if self.has_if == True:
                if self.dfs(NODE._children[0]) == False:
                    return False
            return
        elif NODE.getData() == '[ELIF]':
            if self.has_if == True:
                self.dfs(NODE._children[0])
                if NODE._children[0].getVal() == True:
                    if self.dfs(NODE._children[1]) == False:
                        return False
                    self.has_if = False
                else:
                    self.has_if = True
            return
        self.has_if = False

        if NODE.getData() == '[function]':
            self.FunctionTable[NODE._children[0].getData()] = NODE
            return
        elif NODE.getData() == '[RETURN]':
            self.dfs(NODE._children[0])
            if NODE._children[0].getData() == '[None]':
                self.RETURN.append('None')
            elif NODE._children[0].getVal() != None:
                self.RETURN.append(NODE._children[0].getVal())
            else:
                self.RETURN.append(self.VariableTable[NODE._children[0].getData()])
            return
        elif NODE.getData() == '[runFunction]':
            self.RETURN = []
            FuncNode = self.FunctionTable[NODE._children[0].getData()]
            self.paraList = []
            if len(NODE._children)==2:
                for para in range(len(NODE._children[1].getChildren())):
                    self.dfs(NODE._children[1].getChildren()[para])
                    val = NODE._children[1].getChildren()[para].getVal()
                    if val==None:
                        val = self.VariableTable[NODE._children[1].getChildren()[para].getData()]
                    paraName = FuncNode.getChildren()[1].getChildren()[para].getData()
                    self.paraList.append((paraName,val))
            t = Tran()
            for para in self.paraList:
                t.VariableTable[para[0]] = para[1]
            t.FunctionTable = copy.copy(self.FunctionTable)
            if len(NODE._children)==2:
                t.dfs(FuncNode.getChildren()[2])
            else:
                t.dfs(FuncNode.getChildren()[1])

            if t.RETURN!=[]:
                NODE.setVal(t.RETURN[0])
            else:
                NODE.setVal("None")

        if NODE.getData() == '[WHILE]':
            while True:
                self.dfs(NODE._children[0])
                if NODE._children[0].getVal() == True:
                    if self.dfs(NODE._children[1]) == False:
                        return
                else:
                    break
            return
        elif NODE.getData() == '[FOR]':
            self.dfs(NODE._children[0])
            while True:
                self.dfs(NODE._children[1])
                if NODE._children[1].getVal() == True:
                    if self.dfs(NODE._children[3]) == False:
                        return
                    self.VariableTable[NODE._children[2].getData()] += 1
                else:
                    break
            return

        if NODE._children != []:
            for i in range(len(NODE._children)):
                if NODE._children[i].getData() == '[BREAK]':
                    return False
                if self.dfs(NODE._children[i]) == False:
                    return False
        else:
            return

        if NODE.getData() == '[PRINT]':
            for child in range(len(NODE._children)):
                if child != len(NODE._children) - 1:
                    if NODE._children[child].getVal() != None:
                        print(NODE._children[child].getVal(), end=' ')
                    else:
                        print(self.VariableTable[NODE._children[child].getData()], end=' ')
                else:
                    if NODE._children[child].getVal() != None:
                        print(NODE._children[child].getVal())
                    else:
                        print(self.VariableTable[NODE._children[child].getData()])

        elif NODE.getData() == '[assignment]':
            if NODE._children[0].getData() == '[array_term]':
                var = NODE._children[0].getChildren()[0].getData()
                index = NODE._children[0].getChildren()[1].getVal()
                if index == None:
                    index = self.VariableTable[NODE._children[0].getChildren()[1].getData()]
                self.VariableTable[var][index] = NODE.getChildren()[1].getVal() if NODE.getChildren()[1].getVal() != None else self.VariableTable[NODE._children[1].getData()]
            self.VariableTable[NODE._children[0].getData()] = NODE.getChildren()[1].getVal() if NODE.getChildren()[1].getVal() != None else self.VariableTable[NODE._children[1].getData()]

        elif NODE.getData() == '[array]':
            arr = []
            children = NODE._children[0]._children
            for child in range(len(children)):
                if children[child].getVal() != None:
                    arr.append(children[child].getVal())
                else:
                    arr.append(self.VariableTable[children[child].getData()])
            NODE.setVal(arr)

        elif NODE.getData() == '[array_term]':
            arr = self.VariableTable[NODE._children[0].getData()]
            term = self.VariableTable[NODE._children[1].getData()] if NODE._children[1].getVal() == None else NODE._children[
                1].getVal()
            NODE.setVal(arr[term])

        elif NODE.getData() == '[LEN]':
            NODE.setVal(len(self.VariableTable[NODE._children[0].getData()]))

        elif NODE.getData() == '[ADD]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]

            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            NODE.setVal(c1_val + c2_val)

        elif NODE.getData() == '[SUB]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            NODE.setVal(c1_val - c2_val)

        elif NODE.getData() == '[MUL]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            NODE.setVal(c1_val * c2_val)

        elif NODE.getData() == '[DIV]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            assert c1_val / c2_val
            NODE.setVal(c1_val / c2_val)

        elif NODE.getData() == '[DIV_ext]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            assert c1_val // c2_val
            NODE.setVal(c1_val // c2_val)
        elif NODE.getData() == '[AND]':
            self.dfs(NODE._children[0])
            self.dfs(NODE._children[1])
            if NODE._children[0].getVal() == True and NODE._children[1].getVal() == True:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData() == '[OR]':
            self.dfs(NODE._children[0])
            self.dfs(NODE._children[1])
            if NODE._children[0].getVal() == True or NODE._children[1].getVal() == True:
                NODE.setVal(True)
            else:
                NODE.setVal(False)

        elif NODE.getData() == '[less]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            if c1_val < c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData() == '[greater]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            if c1_val > c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData() == '[equal_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            if c1_val == c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData() == '[greater_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            if c1_val >= c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData() == '[less_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val == None:
                c1_val = self.VariableTable[child1.getData()]
            if c2_val == None:
                c2_val = self.VariableTable[child2.getData()]
            if c1_val <= c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)

