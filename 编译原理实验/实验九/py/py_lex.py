import ply.lex as lex

tokens = ['PRINT','NUMBER','VARIABLE','LP','RP']

literals=['=','+','-','*','/','(',')','{','}','<','>',',']

def t_NUMBER(t):
    '[0-9]+'
    return t

def t_LP(t):
    '\('
    return t

def t_RP(t):
    '\)'
    return t

def t_PRINT(t):
    r'print'
    return t

def t_VARIABLE(t):
    '[a-zA-Z_][a-zA-Z0-9_]*'
    return t

t_ignore = " \t"

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)


lex.lex()
# data = 'a = a+c'
# lexer = lex.lex()
# lexer.input(data)
# while True:
#     tok = lexer.token()
#     if not tok:
#         break
#     print(tok)