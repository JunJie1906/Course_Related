import re
from html2pdf import html2pdf 

# 规则化字符串，每个单词空一个空格
def Clear(abstracts):
    abstracts = abstracts.split()
    for i in range(len(abstracts)):
        abstracts[i] += ' '
    return ''.join(abstracts)

# 1. read tex file
content=open('example.tex','r').read()


# 2. extract document part
p_doc=re.compile(r'\\begin{document}(.+?)\\end{document}',re.S)
document= p_doc.findall(content)[0]
# print(document)

# 3.extract and remove 注释
p_zhushi = re.compile(r'%.+?\n',re.S)
zhushi = p_zhushi.findall(document)
for i in zhushi:
    document = document.replace(i,'')
    # print(i)
document.replace("\\{",'{')
document.replace("\\}",'}')

# 4. extract and modify head
p_title=re.compile(r'(\\title{(.+?)})',re.S)
title=p_title.findall(document)
for i in title:
    document = document.replace(i[0],'<h1 align="center">%s<h1>'%i[1])
document = document.replace("\\maketitle",'')


# 5. extract and remove emph
p_emph = re.compile(r'(\\emph{(.+?)})',re.S)
emph = p_emph.findall(document)
for i in range(len(emph)):
    document = document.replace(emph[i][0],emph[i][1])



# 6. extract and remove texttt
p_texttt = re.compile(r'(\\texttt{(.+?)})')
textt = p_texttt.findall(document)
for i in textt:
    document = document.replace(i[0],i[1])


# 7. extract and delete date (html里面无法获取当前时间，没法调用js，直接删除)
p_date = re.compile(r'(\\date{(.+?)})')
date = p_date.findall(document)
for i in date:
    document = document.replace(i[0],'')

# 8. extract and modify author
p_author = re.compile(r'(\\author{(.+?)})',re.S)
author = p_author.findall(document)
for i in range(len(author)):
    aut = author[0][1]
    aut = aut.replace('\\','\n')
    crt = aut.split('\n')
    aut = ""
    for i in crt:
        if Clear(i) == ' ' or Clear(i)=='':
            continue
        aut+='<h6 align = "center">%s</h6>' %Clear(i)
    document = document.replace(author[0][0], '%s' % aut)
# print(aut)


# 9. extract and modify abstract
p_abs=re.compile(r'(\\begin{abstract}(.+?)\\end{abstract})',re.S)
abstract = p_abs.findall(document)
for i in range(len(abstract)):
    abstracts = Clear(abstract[i][1])
    document = document.replace(abstract[i][0],'<h3 align="center"><b>abstract</b></h3><p>%s</p>'%abstracts)


# 10. extract and modify sections

# (1) section层
p_section = re.compile(r'(\\section{(.+?)}(.+?))\\begin{thebibliography}',re.S)
section = p_section.findall(document)
for i in range(len(section)):
    document = document.replace(section[i][0],'<ol><h3><li><b>%s</b></h3>%s</ol>'%(section[i][1],section[i][2]))

# (2) subsection层
p_subsection = re.compile(r'(\\subsection{(.+?)}(.+?))(\\begin{thebibliography}|\\section{)',re.S)
subsection = p_subsection.findall(document)
for i in range(len(subsection)):
    document = document.replace(subsection[i][0],'<ol><h3><li><b>%s</b></h3>%s</ol>'%(subsection[i][1],subsection[i][2]))

# (3) subsubsection层
p_subsubsection = re.compile(r'(\\subsubsection{(.+?)}(.+?))(\\begin{thebibliography}|\\section{|\\subsection{)',re.S)
subsubsection = p_subsubsection.findall(document)
for i in range(len(subsubsection)):
    document = document.replace(subsubsection[i][0],'<ol><h3><li><b>%s</b></h3>%s</ol>'%(subsubsection[i][1],subsubsection[i][2]))

# (4) 中间的 sections
p_sections = re.compile(r'(\\(sub)*section{(.+?)}(.+?)(<ol>|</ol>))',re.S)
sections = p_sections.findall(document)
# print(sections[0][3])
for i in range(len(sections)):
    document = document.replace(sections[i][0],'<h3><li><b>%s</b></h3><p>%s</p>'%(sections[i][2],sections[i][3]))


# 11. extract and modify textbf
p_textbf = re.compile(r'(\\textbf{(.+?)})',re.S)
textbf = p_textbf.findall(document)
for i in range(len(textbf)):
    document = document.replace(textbf[i][0],'<strong>%s</strong>'%textbf[i][1])

# print(textbf)

# 12. extract and modify itemize

document = document.replace('\\begin{itemize}','<ul>')
document = document.replace('\\end{itemize}','</ul>')
document = document.replace('\\item','<li>')

# 13. extract and remove \textbackslash

document = document.replace('\\textbackslash','\\')

# 14. center标签
document = document.replace('\\begin{center}','<p align="center">')
document = document.replace('\\end{center}','</p>')


# 15.把tabular变成html表格

# 提取tabular所有内容
p_tabular = re.compile(r'((\\begin{tabular}{.*?}).+?(\\end{tabular}))',re.S)
tabular = p_tabular.findall(document)

for i in range(len(tabular)):
    table = tabular[i][0]
    table1 = tabular[i][0]
    table = table.replace("\\\\",'\n')
    table = table.replace("\\hline",'\n')
    tb = table.split("\n")
    # 把空字符去掉
    while i<len(tb):
        tb[i] = tb[i].replace(' ','')
        tb[i] = tb[i].replace('\t','')
        tb[i] = tb[i].replace('\n','')
        if tb[i]=='':
            tb.remove(tb[i])
        else:
            i += 1

    # print(tb)
    thead = ''
    p = tb[0].count('|',0,len(tb[0]))-1 # 每一行的个数

    crt = tb[1]
    for i in range(p):
        c = crt.find("&")
        if c!=-1:
            thead+='<th width="1"  style="text-align:left;">' #这里删除width后就报错。。。
            thead+=crt[0:c]
            thead+='</th>'
            crt = crt[c+1:]
        else:
            thead+='<th width="1"  style="text-align:left;">'
            thead+=crt
            thead+='</th>'
    table = ''
    thead = "<thead><tr>%s</tr></thead>"%thead
    # print(thead)

    tbody = ''
    n = 2
    while n<len(tb):
        crt = tb[n]
        n = n + 1
        do = ""
        for i in range(p):
            c = crt.find("&")
            # print(crt)
            if c != -1:
                do += "<td>%s </td>" % crt[0:c]
                crt = crt[c + 1:]
            else:
                do += "<td>%s </td>" % crt
                # print(crt)
        # print(do)
        tbody+='<tr>%s</tr>'%do
    tbody1 = '<tbody>'
    tbody1+= tbody
    tbody1+='</tbody>'
    table +='<table border = "1" width="50%">'
    table +=thead
    table +=tbody1
    table +="</table>"
    document = document.replace(table1,table)

# 16. abstract and remove thebibliography 这里面标签太多，直接删除了吧
p_the = re.compile(r'\\begin{thebibliography}.+?\\end{thebibliography}',re.S)
thbibliography = p_the.findall(document)
document = document.replace(thbibliography[0],'')

#  17. generate html text

html2pdf(document,'result.pdf')