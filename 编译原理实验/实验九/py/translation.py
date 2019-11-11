from py_syn import *
from utils import *

def trans_py(text):
    Parse = yacc.parse(clear_text(text))
    # Parse.print_node(0)
    def dfs(NODE):
        if NODE._children!=[]:
            for i in range(len(NODE._children)):
                dfs(NODE._children[i])
        else:
            return
        if NODE.getData()=='[assignment]':
            VaribleTable[NODE._children[0].getData()] = NODE.getChildren()[1].getVal()



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

    dfs(Parse)

    return Parse







