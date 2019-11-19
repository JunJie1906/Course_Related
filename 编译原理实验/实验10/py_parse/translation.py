from py_syn import *
from utils import *

def trans_py(text):
    Parse = yacc.parse(clear_text(text))
    Parse.print_node(0)
    def dfs(NODE):
        if NODE._children!=[]:
            for i in range(len(NODE._children)):
                dfs(NODE._children[i])
        else:
            return
        if NODE.getData()=='[assignment]':
            if NODE._children[0].getData()=='[array_term]':
                var = NODE._children[0].getChildren()[0].getData()
                index = NODE._children[0].getChildren()[1].getVal()
                VaribleTable[var][index] = NODE.getChildren()[1].getVal() if NODE.getChildren()[1].getVal()!=None else VaribleTable[NODE._children[1].getData()]

            VaribleTable[NODE._children[0].getData()] = NODE.getChildren()[1].getVal() if NODE.getChildren()[1].getVal()!=None else VaribleTable[NODE._children[1].getData()]

        elif NODE.getData()=='[array]':
            arr = []
            children = NODE._children[0]._children
            for child in range(len(children)):
                if children[child].getVal()!=None:
                    arr.append(children[child].getVal())
                else:
                    arr.append(VaribleTable[children[child].getData()])
            NODE.setVal(arr)
        elif NODE.getData()=='[array_term]':
            arr = VaribleTable[NODE._children[0].getData()]
            term = VaribleTable[NODE._children[1].getData()] if NODE._children[1].getVal()==None else NODE._children[1].getVal()
            NODE.setVal(arr[term])


        elif NODE.getData()=='[ADD]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            NODE.setVal(c1_val+c2_val)

        elif NODE.getData()=='[SUB]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            NODE.setVal(c1_val-c2_val)

        elif NODE.getData()=='[MUL]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            NODE.setVal(c1_val*c2_val)

        elif NODE.getData()=='[DIV]':

            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            assert c1_val/c2_val
            NODE.setVal(c1_val/c2_val)
        elif NODE.getData()=='[less]':
            children = NODE._children
            con1 = children[0].getVal()
            con2 = children[1].getVal()
            if con1<con2:
                NODE.setVal(True)
            else:
                NODE.setVal(False)


    dfs(Parse)

    return Parse







