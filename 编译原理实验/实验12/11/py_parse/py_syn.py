import ply.yacc as yacc
from py_lex import *
from Node import*

def p_segment(t):
    'segment : statements'
    t[0] = node('[segment]')
    t[0].add(t[1])

def p_statements(t):
    '''statements : statements statement
                  | statement'''
    if len(t)==3:
        t[0] = t[1]
        t[0].add(t[2])
    elif len(t)==2:
        t[0] = node('[statements]')
        t[0].add(t[1])

def p_statement(t):
    '''
    statement : assignment
             | operation
             | print
             | if
             | else
             | elif
             | while
             | break
             | for
             | function
             | runFunction
             | return
             | class
             | method
    '''
    t[0] = node(t[1])

def p_class(t):
    '''
    class : CLASS VARIABLE '{' classFunctions '}'
          | CLASS VARIABLE '{' '}'
    '''
    t[0] = node('[class]')
    if len(t)==6:
        t[0].add(node(t[2]))
        t[0].add(node(t[4]))
    else:
        t[0].add(node(t[2]))



# def p_classTerm(t):
#     '''
#     classTerm : Variable '.'
#     '''

def p_classMem(t):
    '''
    classMem : VARIABLE '.' VARIABLE
    '''
    t[0] = node('[classMem]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_method(t):
    '''
    method : classMem '(' ')'
           | classMem '(' runFunctionTerms ')'
    '''
    t[0] = node('[method]')
    if len(t)==4:
        t[0].add(t[1])
    else:
        t[0].add(t[1])
        t[0].add(node(t[3]))


def p_classFunctions(t):
    '''
    classFunctions : function
                  | initClass
              | classFunctions function
              | classFunctions initClass
    '''

    if len(t)==2:
        t[0] = node('[classFunctions]')
        t[0].add(node(t[1]))
    else:
        t[0] = node(t[1])
        t[0].add(node(t[2]))
#
def p_initClass(t):
    '''
    initClass : DEF INIT '(' runFunctionTerms ')'  '{' statements '}'
    '''
    t[0] = node('[__init__]')
    t[0].add(node(t[4]))
    t[0].add(node(t[7]))

def p_return(t):
    '''return : RETURN
              | RETURN term
    '''
    t[0] = node('[RETURN]')

    if len(t)==3:
        t[0].add(node(t[2]))
    elif len(t) == 2:
        t[0].add(node('[None]'))

def p_function(t):
    '''
    function : DEF VARIABLE '(' functionTerms ')'  '{' statements '}'
             | DEF VARIABLE '('  ')'  '{' statements '}'
    '''
    if len(t)==9:
        t[0] = node('[function]')
        t[0].add(node(t[2]))
        t[0].add(node(t[4]))
        t[0].add(node(t[7]))
    else:
        t[0] = node('[function]')
        t[0].add(node(t[2]))
        t[0].add(node(t[6]))


def p_runFunction(t):
    '''
    runFunction : VARIABLE '(' runFunctionTerms ')'
                | VARIABLE '('  ')'
    '''
    if len(t)==5:
        t[0] = node('[runFunction]')
        t[0].add(node(t[1]))
        t[0].add(node(t[3]))
    else:
        t[0] = node('[runFunction]')
        t[0].add(node(t[1]))

def p_runFunctionTerms(t):
    '''
    runFunctionTerms : term
                  | runFunctionTerms ',' term
    '''
    if len(t)==2:
        t[0] = node('[runFunctionTerms]')
        t[0].add(node(t[1]))
    elif len(t)==4:
        t[0] = node(t[1])
        t[0].add(node(t[3]))

def p_functionTerms(t):
    '''
    functionTerms : VARIABLE
                  | functionTerms ',' VARIABLE
    '''
    if len(t) == 2:
        t[0] = node('[functionTerms]')
        t[0].add(node(t[1]))
    elif len(t) == 4:
        t[0] = node(t[1])
        t[0].add(node(t[3]))

def p_BREAK(t):
    '''
    break : BREAK
    '''
    t[0] = node('[BREAK]')

def p_while(t):
    '''
    while : WHILE '(' condition ')' '{' statements '}'
    '''
    t[0] = node('[WHILE]')
    t[0].add(t[3])
    t[0].add(t[6])

#只写了i++
def p_for(t):
    '''
    for : FOR '(' assignment ';' condition ';' VARIABLE '+' '+' ')' '{' statements '}'
    '''
    t[0] = node('[FOR]')
    t[0].add(t[3])
    t[0].add(t[5])
    t[0].add(node(t[7]))
    t[0].add(t[12])

def p_if(t):
    '''
    if : IF '(' condition ')' '{' statements '}'
    '''
    t[0] = node('[IF]')
    t[0].add(node(t[3]))
    t[0].add(node(t[6]))

def p_else(t):
    '''
    else : ELSE '{' statements '}'
    '''
    t[0] = node('[ELSE]')
    t[0].add(t[3])

def p_elif(t):
    '''
    elif : ELIF '(' condition ')' '{' statements '}'
    '''
    t[0] = node('[ELIF]')
    t[0].add(node(t[3]))
    t[0].add(node(t[6]))

def p_and(t):
    '''
    and : condition AND condition
    '''
    t[0] = node('[AND]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))



def p_or(t):
    '''
    or : condition OR condition
    '''
    t[0] = node('[OR]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_condition(t):
    '''
    condition : greater
              | greater_equal
              | less
              | less_equal
              | equal_equal
              | and
              | or
    '''
    t[0] = node(t[1])

def p_greater(t):
    '''
    greater   : term '>' term
              '''
    t[0] = node('[greater]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_greater_equal(t):
    '''
    greater_equal   : term '>' '=' term
              '''
    t[0] = node('[greater_equal]')
    t[0].add(node(t[1]))
    t[0].add(node(t[4]))


def p_less(t):
    '''
    less   : term '<' term
              '''
    t[0] = node('[less]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_less_equal(t):
    '''
    less_equal   : term '<' '=' term
              '''
    t[0] = node('[less_equal]')
    t[0].add(node(t[1]))
    t[0].add(node(t[4]))

def p_equal_equal(t):
    '''
    equal_equal   : term '=' '=' term
              '''
    t[0] = node('[equal_equal]')
    t[0].add(node(t[1]))
    t[0].add(node(t[4]))

def p_assignment(t):
    '''
    assignment : VARIABLE '=' term
                | VARIABLE '=' array
                | array_term '=' term
                | term '=' term
                | VARIABLE '+' '=' term
                | array_term '+' '=' term
                | VARIABLE '-' '=' term
                | array_term '-' '=' term
                | VARIABLE '*' '=' term
                | array_term '*' '=' term
                | VARIABLE '/' '=' term
                | array_term '/' '=' term
    '''
    t[0] = node('[assignment]')


    if len(t)==4:
        t[0].add(node(t[1]))
        t[0].add(node(t[3]))
    elif len(t)==5:
        t[0].add(node(t[1]))
        if t[2] == '+':
            crt = node('[ADD]')
        elif t[2] == '-':
            crt = node('[SUB]')
        elif t[2] == '*':
            crt = node('[MUL]')
        elif t[2] == '/':
            crt = node('[DIV]')
        crt.add(node(t[1]))
        crt.add(node(t[4]))
        t[0].add(crt)

def p_operation(t):
    '''
    operation : ADD
              | SUB
              | MUL
              | DIV
              | DIV_ext
              | '(' operation ')'
    '''
    if len(t)==2:
        t[0] = node(t[1])
    else:
        t[0] = node(t[2])

def p_ADD(t):
    '''
    ADD : term '+' term

    '''
    t[0] = node('[ADD]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_SUB(t):
    '''
    SUB : term '-' term
    '''
    t[0] = node('[SUB]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_MUL(t):
    '''
    MUL : term '*' term

    '''
    t[0] = node('[MUL]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_DIV(t):
    '''
    DIV : term '/' term
    '''
    t[0] = node('[DIV]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))
#整除//
def p_DIV_ext(t):
    '''
    DIV_ext : term '/' '/' term
    '''
    t[0] = node('[DIV_ext]')
    t[0].add(node(t[1]))
    t[0].add(node(t[4]))

def p_print(t):
    '''print : PRINT '(' pcontent ')' '''
    t[0] = node(t[3])
    t[0]._data = '[PRINT]'

# add
def p_array_term(t):
    '''
     array_term : VARIABLE '[' term ']'
    '''
    t[0] = node('[array_term]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

# add
def p_array(t):
    '''
    array : '[' pcontent ']'
    '''
    t[0] = node('[array]')
    t[0].add(node(t[2]))


def p_pcontent(t):
    '''
    pcontent : pcontent ',' term
             | term
    '''
    if len(t)==2:
        t[0] = node('[print_content]')
        t[0].add(node(t[1]))
    elif len(t) == 4:
        t[0] = node(t[1])
        t[0].add(node(t[3]))

def p_string(t):
    '''
    string : quote String quote
          | quote VARIABLE quote
    '''
    t[0] = node('[string]')
    t[0].add(node(t[2]))

def p_term(t):
    '''
    term : VARIABLE
         | NUMBER
         | operation
         | array_term
         | len
         | runFunction
         | method
         | classMem
         | string
    '''
    if len(t)==2:
        t[0] = t[1]

def p_len(t):
    '''
    len : LEN '(' VARIABLE ')'
    '''
    t[0] = node('[LEN]')
    t[0].add(node(t[3]))

def p_error(t):
    print("Syntax error at '%s'" % t.value)

yacc.yacc()

p = yacc.parse