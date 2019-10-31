import re
from fpdf import FPDF, HTMLMixin


# 正文需要把"\n"给换成空格
def clear_text(text):
    lines=[]
    for line in text.split('\n'):
        line=line.strip()
        if len(line)>0:
            lines.append(line)
    return ' '.join(lines)

#读取文件
f = open('example.tex','r')
document = f.read()
f.close()

#换LaTeX成正规文字
document = document.replace('\\LaTeX{}','LaTeX')

#读取latex正文
p_doc=re.compile(r'\\begin{document}(.+?)\\end{document}',re.S)
document=p_doc.findall(document)[0]

#去掉注释
p = re.compile(r'(%.+?)\n')
for i in p.findall(document):
    zhushi = '<!--%s-->'% i
    document = document.replace(i,zhushi)

document=document.replace(r'\\LaTeX\{\}',r'LaTeX')

#去掉时间戳
document=document.replace(r'\usepackage{times}','')
document=document.replace(r'\date{\today}','')
document=document.replace(r'\maketitle','')
document = document.replace('\\{','{')
document = document.replace('\\}','}')

#替换title标题
p_title=re.compile(r'(\\title{(.+?)})',re.S)
for i in p_title.findall(document):
    title = '<h1 align="center">%s</h1>' % i[1]
    document = document.replace(i[0], title)

# 替换author标题
p_author = re.compile(r'(\\author{(.+?)})', re.S)
for i in p_author.findall(document):
    author = '<h2 align="center">%s</h2>' % clear_text(i[1])
    document = document.replace(i[0], author)

#替换abstrac标题
p_abs=re.compile(r'(\\begin{abstract}(.+?)\\end{abstract})',re.S)
for i in p_abs.findall(document):
    abstrac = '<h3 align="center">abstract</h3><p>%s</p><br/>' % clear_text(i[1])
    document = document.replace(i[0], abstrac)


#替换itemize无序列表
p_bg_itemize = re.compile(r'(\\begin{itemize})', re.S)
document = p_bg_itemize.sub('<ul>',document)
p_ed_itemize = re.compile(r'(\\end{itemize})', re.S)
document = p_ed_itemize.sub('</ul>',document)

#列表项\item
document = document.replace('\\item','<li>')

#对齐方式div布局
p_bg_ct=re.compile(r'(\\begin{center}(.+?)\\end{center})',re.S)
for i in p_bg_ct.findall(document):
    bg_ct = '<div align="center">%s</div>' % i[1]
    document = document.replace(i[0], bg_ct)


#斜体替换
p_emph = re.compile(r'(\\emph{(.+?)})')
for i in p_emph.findall(document):
    emph = '<i>%s</i>'% i[1]
    document = document.replace(i[0],emph)


#texttt等宽字体替换
p_texttt = re.compile(r'(\\texttt{(.+?)}) &')
for i in p_texttt.findall(document):
    texttt = '<tt>%s</tt>'% i[1]
    document = document.replace(i[0],texttt)

#texttt等宽字体替换
p_texttt = re.compile(r'(\\texttt{(.+?)})')
for i in p_texttt.findall(document):
    texttt = '<tt>%s</tt>'% i[1]
    document = document.replace(i[0],texttt)


p_table = re.compile(r'\\begin{tabular}{(.+?)}(.+?)\\end{tabular}',re.S)
m= p_table.findall(document)
s=m[0][1]
m= s.split('\\hline')
p = re.compile(r'\\begin{tabular}{\|(.+?)\|}')
alogin = p.search(document).group(1)
document = document.replace(p.search(document).group(0),'''<table border = "1" width="50%">''')
style = []
for i in alogin:
    i = i.strip()
    if i == 'l':
        style.append('''style="text-align:left;"''')
    elif i == 'c':
        style.append('''style="text-align:center;"''')
    elif i== 'r':
        style.append('''style="text-align:right;"''')
#这么多行
for i in range(1,len(m)-1):         #三条线划分为4部分，最前面和最后面部分无用

    m[i] = m[i].strip()
    if i==1:
        n = m[i].split('&')
        th = ''
        for j in range(len(n)):
            th += '<th %s %s>%s</th>'%('''width="60%" ''',style[j], n[j])
        th = '<thead><tr>%s</tr></thead>'%th
        document = document.replace(m[i],th)
    else:
        p_td=re.compile('[&\n]')
        td_list = p_td.split(m[i])
        td_list=[s.strip() for s in td_list]

        # 这么多列
        td=''
        print(len(td_list))
        for j in range(0,len(td_list),2):
            if j+1<len(td_list):
                td += '<tr><td>%s</td><td>%s</td></tr>' % (td_list[j],td_list[j+1],)
        td = '<tbody>%s</tbody>'%td
        document = document.replace(m[i], td)


#替换section有序列表
#\section{...}  中间的是加入到<ol>..</ol>
p_ol = re.compile(r'(\\section.+?)\\begin{thebibliography}',re.S)
for i in p_ol.findall(document):
    ol = '<ol>\n\t%s</ol>\n\t' % i
    document = document.replace(i, ol)

p_ol = re.compile(r'(\\subsection.+?)\\(section|begin{thebibliography})',re.S)
for i in p_ol.findall(document):
    ol = '<ol>\n\t%s</ol>\n\t' % i[0]
    document = document.replace(i[0], ol)

p_ol = re.compile(r'(\\subsubsection.+?)\\(subsection|section|begin{thebibliography})',re.S)
for i in p_ol.findall(document):
    ol = '<ol>\n\t%s</ol>\n\t' % i[0]
    document = document.replace(i[0], ol)

p_section = re.compile(r'(\\(sub)*section{(.+?)}(.+?)\n\t?)\n',re.S)
for i in p_section.findall(document):
    section = '<h3><li><b>%s</b></li></h3><br/><p>%s</p><br/>' % (i[2], clear_text(i[3]))
    document = document.replace(i[0], section)

p_end = re.compile(r'\\begin{thebibliography}(.+?)\\end{thebibliography}',re.S)
document = document.replace(p_end.search(document).group(),'')
document = document.replace('\\end{tabular}','</table>')
p_l = re.compile(r'\t?\\hline')
document = p_l.sub('',document)
#把LaTeX换行"\\"换成html换行"<br\>"
document = document.replace(r'(\\\\)','(\\textbackslash\\textbackslash)')
document=document.replace(r'\\',r'')
#把latex中的反斜线'\textbackslash' 写成正文中的"\"
document=document.replace('\\textbackslash','\\')


#?????????????????????????????????????????????
# fpdf似乎无法正确生成表格，带有标签的都会占一个单元格
p_tr = re.compile('<tr>(.+?)</tr>',re.S)
p_i = re.compile(r'</?i>')
for i in p_tr.findall(document):
    document=p_i.sub('',document)

p_i = re.compile(r'</?tt>')
for i in p_tr.findall(document):
    document=p_i.sub('',document)


class MyFPDF(FPDF, HTMLMixin):
    pass

def html2pdf(html_text, path):
    pdf = MyFPDF()
    pdf.add_page()
    pdf.write_html(html_text)
    pdf.output(path, 'F')

html2pdf(document,'2.pdf')
print(document)