# coding=utf-8
import ply.lex as lex
import ply.yacc as yacc
import re
from math import *
from node import node

# TOKENS

tokens=('SELECT','FROM','WHERE','ORDER','BY','NAME','AND','OR','COMMA',
        'LP','RP','AVG','BETWEEN','IN','SUM','MAX','MIN',
        'COUNT','NUMBER','AS','DOT','literals','cmp','STAR')

def t_STAR(t):
    r'\*'
    return t

def t_cmp(t):
    r'\> | \< | \='
    return t

def t_literals(t):
    r'= | \+ | \- | \* | \^ | \> | \< '
    return t

def t_SELECT(t):
    r'SELECT'
    return t

def t_FROM(t):
	r'FROM'
	return t

def t_WHERE(t):
	r'WHERE'
	return t

def t_ORDER(t):
	r'ORDER'
	return t

def t_BY(t):
	r'BY'
	return t

def t_AND(t):
	r'AND'
	return t

def t_OR(t):
	r'OR'
	return t

def t_COMMA(t):
	r','
	return t

def t_LP(t):
	r'\('
	return t

def t_RP(t):
	r'\)'
	return t

def t_AVG(t):
	r'AVG'
	return t

def t_BETWEEN(t):
	r'BETWEEN'
	return t

def t_IN(t):
	r'IN'
	return t

def t_SUM(t):
	r'SUM'
	return t

def t_MAX(t):
	r'MAX'
	return t

def t_MIN(t):
	r'MIN'
	return t

def t_COUNT(t):
	r'COUNT'
	return t


def t_AS(t):
	r'AS'
	return t

def t_DOT(t):
	r'\.'
	return t

def t_NAME(t):
    r'[A-Za-z]+|[a-zA-Z_][a-zA-Z0-9_]*|[A-Z]*\.[A-Z]$'
    return t

def t_NUMBER(t):
    r'[1-9][0-9]*'
    return t

# IGNORED
t_ignore = " \t"

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

lex.lex()


# PARSING
def p_query(t):
    '''query :  select
             | LP query RP'''
    if len(t)<3:
        t[0] = t[1]
    else:
        t[0] = t[2]
    return t

def p_select(t):
    '''
    select :  SELECT list FROM table WHERE lst ORDER BY list
       | SELECT list FROM table WHERE lst
       | SELECT list FROM table ORDER BY list
       | SELECT list FROM table
    '''
    t[0] = node('QUERY')
    t[0].add(node('[SELECT]'))
    t[0].add(t[2])
    t[0].add(node('[FROM]'))
    t[0].add(t[4])
    if len(t)==8:
        t[0].add(node('[ORDER BY]'))
        t[0].add(t[7])
    elif len(t)==7:
        t[0].add(node('[WHERE]'))
        t[0].add(t[6])
    elif len(t)==10:
        t[0].add(node('[WHERE]'))
        t[0].add(t[6])
        t[0].add(node('[ORDER]'))
        t[0].add(node('[BY]'))
        t[0].add(t[9])
    return t

def p_table(t):
    '''
    table :  NAME
       | LP query RP
       | table COMMA table
    '''
    if len(t)==2:
        t[0] = node('[TABLE]')
        t[0].add(node(t[1]))
    elif t[1]=='(':
        t[0] = node('[TABLE]')
        t[0].add(t[2])
    elif isinstance(t[3],node)==True:
        t[0] = node(t[1])
        t[0].add(node('[COMMA]'))
        t[0].add(node(t[3]))
    return t


def p_lst(t):
    '''
    lst : condition
       | condition AND condition
       | condition OR condition
       | NAME BETWEEN NUMBER AND NUMBER
       | NAME IN LP query RP
       | NAME literals agg
       | agg literals NUMBER
'''
    t[0] = node('[lst]')
    if len(t)==2:
        t[0].add(node(t[1]))
    elif t[2] == 'AND' :
        t[0].add(node(t[1]))
        t[0].add(node('[AND]'))
        t[0].add(node(t[3]))
    elif t[2] == 'OR':
        t[0].add(node(t[1]))
        t[0].add(node('[OR]'))
        t[0].add(node(t[3]))
    elif t[2] == 'BETWEEN':
        t[0].add(node(t[1]))
        t[0].add(node('[BETWEEN]'))
        t[0].add(node(t[3]))
        t[0].add(node('[AND]'))
        t[0].add(node(t[5]))
    elif t[2] == 'IN':
        t[0].add(node(t[1]))
        t[0].add(node('[IN]'))
        t[0].add(node(t[4]))
    else:
        t[0].add(node(t[1]))
        t[0].add(node(t[2]))
        t[0].add(node(t[3]))
    return t

def p_condition(t):
    ''' condition : NAME cmp NUMBER
                  '''
    t[0]=node('[TERM]')
    if isinstance(t[1], node)==False:
        t[0].add(node(str(t[1])))
        t[0].add(node(t[2]))
        t[0].add(node(t[3]))
    return t

def p_agg(t):
    '''
    agg : SUM LP NAME RP
         | AVG LP NAME RP
         | COUNT LP NAME RP
         | MIN LP NAME RP
         | MAX LP NAME RP
'''
    t[0] = node('[agg]')

    if t[1]=='SUM':
        t[0].add(node('[SUM]'))
    elif t[1] == 'AVG':
        t[0].add(node('[AVG]'))
    elif t[1] == 'COUNT':
        t[0].add(node('[COUNT]'))
    elif t[1] == 'MIN':
        t[0].add(node('[MIN]'))
    elif t[1] == 'MAX':
        t[0].add(node('[MAX]'))
    t[0].add(node(t[3]))
    return t

def p_list(t):
    '''
    list : STAR
         | NAME
         | NAME DOT NAME
         | list COMMA list
         | list AND NAME
         | list OR NAME
        | NAME AS NAME
        | list AS NAME
         | agg
'''
    if len(t)==2:
        t[0] = node('[LIST]')
        t[0].add(node(t[1]))

    elif t[2] == '.':
        t[0] = node('[LIST]')
        t[0].add(node(t[1]))
        t[0].add(node('[DOT]'))
        t[0].add(node(t[3]))
    elif t[2] == ',':
        t[0] = node(t[1])
        t[0].add(node('[COMMA]'))
        t[0].add(node(t[3]))
    elif t[2] == 'AND':
        t[0] = node(t[1])
        t[0].add(node('[AND]'))
        t[0].add(node(t[3]))
    elif t[2] == 'OR':
        t[0] = node(t[1])
        t[0].add(node('[OR]'))
        t[0].add(node(t[3]))
    elif t[2] =='AS':
        if isinstance(t[1],node):
            t[0] = node(t[1])
        else:
            t[0] = node('[LIST]')
            t[0].add(node(t[1]))
        t[0].add(node('[AS]'))
        t[0].add(node(t[3]))
    return t

def p_error(p):
    print(" Syntax error in input!")



yacc.yacc()


query1 = 'SELECT STU.one AS one, TEACHER.two AS two  FROM STU,TEACHER WHERE score>80 AND ONLINE>90  ORDER BY score '
parse1 = yacc.parse(query1)
parse1.print_node()

query2 = 'SELECT AVG ( sage ) AS average FROM (SELECT w,b FROM STU) WHERE sage>20'
parse2 = yacc.parse(query2)
parse2.print_node()

query3 = 'SELECT * FROM p WHERE O=2'
parse3 = yacc.parse(query3)
parse3.print_node()
