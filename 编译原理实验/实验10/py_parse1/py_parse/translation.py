from py_syn import *
from utils import *

global has_if
has_if = False
def trans_py(text,print_node = False):
    Parse = yacc.parse(clear_text(text))
    if print_node==True:
        Parse.print_node(0)
    def dfs(NODE):
        global has_if
        if NODE.getData()=='[IF]':
            dfs(NODE._children[0])
            if NODE._children[0].getVal()==True:
                if dfs(NODE._children[1])==False:
                    return False
                has_if = False
            else:
                has_if = True
            return
        elif NODE.getData()=='[ELSE]':
            if has_if == True:
                if dfs(NODE._children[0])==False:
                    return False
            return
        elif NODE.getData()=='[ELIF]':
            if has_if==True:
                dfs(NODE._children[0])
                if NODE._children[0].getVal() == True:
                    if dfs(NODE._children[1]) == False:
                        return False
                    has_if = False
                else:
                    has_if = True
            return
        has_if = False

        if NODE.getData()=='[WHILE]':
            while True:
                dfs(NODE._children[0])
                if NODE._children[0].getVal()==True:
                    if dfs(NODE._children[1]) ==False:
                        return
                else:
                    break
            return
        elif NODE.getData()=='[FOR]':
            dfs(NODE._children[0])
            while True:
                dfs(NODE._children[1])
                if NODE._children[1].getVal()==True:
                    if dfs(NODE._children[3])==False:
                        return

                    VaribleTable[NODE._children[2].getData()]+=1
                else:
                    break
            return

        if NODE._children!=[]:
            for i in range(len(NODE._children)):
                if NODE._children[i].getData()=='[BREAK]':
                    return False
                if dfs(NODE._children[i])==False:
                    return False
        else:
            return

        if NODE.getData()=='[PRINT]':
            for child in range(len(NODE._children)):
                if child!=len(NODE._children)-1:
                    if NODE._children[child].getVal()!=None:
                        print(NODE._children[child].getVal(),end=' ')
                    else:
                        print(VaribleTable[NODE._children[child].getData()],end=' ')
                else:
                    if NODE._children[child].getVal()!=None:
                        print(NODE._children[child].getVal())
                    else:
                        print(VaribleTable[NODE._children[child].getData()])

        elif NODE.getData()=='[assignment]':
            if NODE._children[0].getData()=='[array_term]':
                var = NODE._children[0].getChildren()[0].getData()
                index = NODE._children[0].getChildren()[1].getVal()
                if index ==None:
                    index = VaribleTable[NODE._children[0].getChildren()[1].getData()]
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
        elif NODE.getData()=='[LEN]':
            NODE.setVal(len(VaribleTable[NODE._children[0].getData()]))
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

        elif NODE.getData()=='[DIV_ext]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            assert c1_val//c2_val
            NODE.setVal(c1_val//c2_val)

        elif NODE.getData()=='[less]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            if c1_val<c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData()=='[greater]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            if c1_val>c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData()=='[equal_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            if c1_val==c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData()=='[greater_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            if c1_val>=c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
        elif NODE.getData()=='[less_equal]':
            child1 = NODE.getChildren()[0]
            child2 = NODE.getChildren()[1]
            c1_val = child1.getVal()
            c2_val = child2.getVal()
            if c1_val==None:
                c1_val = VaribleTable[child1.getData()]
            if c2_val==None:
                c2_val = VaribleTable[child2.getData()]
            if c1_val<=c2_val:
                NODE.setVal(True)
            else:
                NODE.setVal(False)
    dfs(Parse)
    return Parse


