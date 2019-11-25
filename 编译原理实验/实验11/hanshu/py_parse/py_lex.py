import ply.lex as lex

tokens = ['PRINT','NUMBER','VARIABLE','IF','ELSE','RETURN','ELIF','WHILE','FOR','BREAK','LEN','DEF','AND','OR']

literals=['=','+','-','*','/','(',')','{','}','<','>',',','[',']',';',':']

def t_DEF(t):
    'def'
    return t

def t_AND(t):
    'and'
    return t

def t_OR(t):
    'or'
    return t

def t_RETURN(t):
    'return'
    return t

def t_BREAK(t):
    'break'
    return t

def t_LEN(t):
    'len'
    return t

def t_FOR(t):
    'for'
    return t

def t_NUMBER(t):
    '[0-9]+'
    return t


def t_WHILE(t):
    'while'
    return t

def t_IF(t):
    'if'
    return t

def t_ELSE(t):
    'else'
    return t

def t_ELIF(t):
    'elif'
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