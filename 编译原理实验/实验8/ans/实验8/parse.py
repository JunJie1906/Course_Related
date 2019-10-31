#! /usr/bin/env python
#coding=utf-8
import ply.lex as lex
import ply.yacc as yacc
from fpdf import FPDF, HTMLMixin


class node:
    def __init__(self, data):
        if isinstance(data,node):
            self._data = data._data
            self._children = data._children
            return
        self._data = data
        self._children = []

    def getdata(self):
        return self._data

    def getchildren(self):
        return self._children

    def add(self, node):
        self._children.append(node)

    def shownode(self):
        for i in self._children:
            if isinstance(i, node):
                i.getHtml()

    def getHtml(self):
        global html
        if self._data=='[DOC]':
            html = html + '<html>'
            self.shownode()
            html = html + '</html>'
        elif self._data=='[CONTENT]':
            html = html + '<body>'
            self.shownode()
            html = html + '</body>'
        elif self._data=='[TITLE]':
            html = html + '<h1 align="center">'
            self.shownode()
            html = html + '</h1>'
        elif self._data =='[AUTHOR]':
            html = html + '<h6 align = "center">'
            self.shownode()
            html = html + '</h6>'
        elif self._data=='[ABSTRACT]':
            html = html + '<h3 align="center"><b>abstract</b></h3><p>'
            self.shownode()
            html = html + '</p>'
        elif self._data=='[SECTIONS]' or self._data=='[SUBSECTIONS]':
            html = html + '<ol>'
            self.shownode()
            html = html + '</ol>'
        elif self._data=='[ITEMIZE]':
            html = html + '<ul>'
            self.shownode()
            html = html + '</ul>'
        elif self._data=='[ITEMS]':
            self.shownode()
        elif self._data=='[ITEM]':
            html = html + '<li>'
            self.shownode()
        elif self._data[:10]=='[SECTION](' :
            html = html + '<h3><li>'
            html = html + self._data[10:-1]
            html = html + '</h3>'
            self.shownode()
        elif self._data[:13]=='[SUBSECTION](':
            html = html + '<h3><li>'
            html = html + self._data[13:-1]
            html = html + '</h3>'
            self.shownode()
        else:
            html = html + self._data

    def print_node(self, prefix):
        print('  ' * prefix, '+', self._data)
        for child in self._children:
            child.print_node(prefix + 1)

def clear_text(text):
    lines=[]
    for line in text.split('\n'):
        line=line.strip()
        if len(line)>0:
            lines.append(line)
    return ' '.join(lines)


# TOKENS
tokens=('TITLE','ABS','DOC','SECTION','TEXT','BEGIN','END','LB','RB','SUBSECTION','ITEMIZE','ITEM','AUTHOR')

#DEFINE OF TOKENS
def t_TITLE(t):
    r'\\title'
    return t

def t_AUTHOR(t):
    r'\\author'
    return t

def t_ITEMIZE(t):
    r'itemize'
    return t

def t_ITEM(t):
    r'\\item'
    return t

def t_DOC(t):
    r'document'
    return t

def t_ABS(t):
    r'abstract'
    return t

def t_SECTION(t):
    r'\\section'
    return t

def t_SUBSECTION(t):
    r'\\subsection'
    return t

def t_TEXT(t):
    r'[0-9a-zA-Z\s\.\,\-]+'
    return t

def t_BEGIN(t):
    r'\\begin'
    return t

def t_END(t):
    r'\\end'
    return t

def t_LB(t):
    r'\{'
    return t

def t_RB(t):
    r'\}'
    return t


# IGNORED
t_ignore = " \t"
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# LEX
lex.lex()

# PARSE
def p_doc(t):
    r'doc : BEGIN LB DOC RB content END LB DOC RB'
    if len(t)==10:
        t[0]=node('[DOC]')
        t[0].add(t[5])

def p_content(t):
    r'''content : title abs sections
                | title author abs sections'''
    if len(t)==4:
        t[0]=node('[CONTENT]')
        t[0].add(t[1])
        t[0].add(t[2])
        t[0].add(t[3])
    else:
        t[0] = node('[CONTENT]')
        t[0].add(t[1])
        t[0].add(t[2])
        t[0].add(t[3])
        t[0].add(t[4])


def p_title(t):
    r'title : TITLE LB TEXT RB'
    if len(t)==5:
        t[0]=node('[TITLE]')
        t[0].add(node(t[3]))

def p_author(t):
    r' author : AUTHOR LB TEXT RB'
    if len(t)==5:
        t[0]=node('[AUTHOR]')
        t[0].add(node(t[3]))

def p_abs(t):
    r'abs : BEGIN LB ABS RB TEXT END LB ABS RB'
    if len(t)==10:
        t[0]=node('[ABSTRACT]')
        t[0].add(node(t[5]))

def p_sections(t):
    '''sections : sections section
                | section'''
    if len(t)==3:
        t[0]=node(t[1])
        t[0].add(t[2])
    if len(t)==2:
        t[0]=node('[SECTIONS]')
        t[0].add(t[1])

def p_section(t):
    r'''section : SECTION LB TEXT RB TEXT
                | section itemize
                | section subsections'''
    if len(t)==6:
        t[0]=node('[SECTION](%s)' %t[3])
        t[0].add(node(t[5]))
    else:
        t[0] = node(t[1])
        t[0].add(t[2])

def p_subsections(t):
    '''subsections : subsections subsection
                | subsection'''
    if len(t)==3:
        t[0]=node(t[1])
        t[0].add(t[2])
    if len(t)==2:
        t[0]=node('[SUBSECTIONS]')
        t[0].add(t[1])

def p_subsection(t):
    r'''subsection : SUBSECTION LB TEXT RB TEXT
                    | subsection itemize '''
    if len(t)==6:
        t[0]=node('[SUBSECTION](%s)' %t[3])
        t[0].add(node(t[5]))
    else:
        t[0] = node('[SUBSECTION]')
        t[0].add(t[1])
        t[0].add(t[2])

def p_itemize(t):
    r'''itemize : BEGIN LB ITEMIZE RB items END LB ITEMIZE RB
                | BEGIN LB ITEMIZE RB itemize END LB ITEMIZE RB'''
    t[0] = node('[ITEMIZE]')
    t[0].add(t[5])

def p_items(t):
    r'''items : item
            | items item'''
    if len(t)==2:
        t[0] = node('[ITEMS]')
        t[0].add(t[1])
    else:
        t[0]= node(t[1])
        t[0].add(t[2])

def p_item(t):
    r'item : ITEM TEXT'
    t[0] = node('[ITEM]')
    t[0].add(node(t[2]))



def p_error(t):
    print("Syntax error at '%s'" % t.value)

data=clear_text(open('example.tex','r').read())

yacc.yacc()
Parse=yacc.parse(data)

Parse.print_node(0)

html = ''
Parse.getHtml()

with open('ans.html','w') as f:
    f.write(html)

class MyFPDF(FPDF, HTMLMixin):
    pass

def html2pdf(html_text, path):
    pdf = MyFPDF()
    pdf.add_page()
    pdf.write_html(html_text)
    pdf.output(path, 'F')

html2pdf(html,'parse.pdf')
