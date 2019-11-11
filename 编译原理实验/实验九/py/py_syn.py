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
    '''
    t[0] = node(t[1])

def p_assignment(t):
    '''
    assignment : VARIABLE '=' VARIABLE
                | VARIABLE '=' operation
                | VARIABLE '=' NUMBER
    '''
    t[0] = node('[assignment]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_operation(t):
    '''
    operation : ADD
              | SUB
              | MUL
              | DIV
    '''
    t[0] = node(t[1])

def p_ADD(t):
    '''
    ADD : NUMBER '+' NUMBER
          | NUMBER '+' VARIABLE
          | VARIABLE '+' VARIABLE
          | VARIABLE '+' NUMBER
          | operation '+' NUMBER
          | operation '+' VARIABLE
    '''
    t[0] = node('[ADD]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_SUB(t):
    '''
    SUB : NUMBER '-' NUMBER
          | NUMBER '-' VARIABLE
          | VARIABLE '-' VARIABLE
          | VARIABLE '-' NUMBER
          | operation '-' NUMBER
          | operation '-' VARIABLE
    '''
    t[0] = node('[SUB]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_MUL(t):
    '''
    MUL : NUMBER '*' NUMBER
          | NUMBER '*' VARIABLE
          | VARIABLE '*' VARIABLE
          | VARIABLE '*' NUMBER
          | operation '*' NUMBER
          | operation '*' VARIABLE
    '''
    t[0] = node('[MUL]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))

def p_DIV(t):
    '''
    DIV : NUMBER '/' NUMBER
          | NUMBER '/' VARIABLE
          | VARIABLE '/' VARIABLE
          | VARIABLE '/' NUMBER
          | operation '/' NUMBER
          | operation '/' VARIABLE
    '''
    t[0] = node('[DIV]')
    t[0].add(node(t[1]))
    t[0].add(node(t[3]))


def p_print(t):
    'print : PRINT LP pcontent RP'
    t[0] = node(t[3])
    t[0]._data = '[PRINT]'


def p_pcontent(t):
    '''
    pcontent : pcontent ',' VARIABLE
             | pcontent ',' NUMBER
             | pcontent ',' operation
             | VARIABLE
             | NUMBER
             | operation
    '''
    if len(t)==2:
        t[0] = node('[print_content]')
        t[0].add(node(t[1]))
    elif len(t) == 4:
        t[0] = node(t[1])
        t[0].add(node(t[3]))

def p_error(t):
    print("Syntax error at '%s'" % t.value)

yacc.yacc()

p = yacc.parse