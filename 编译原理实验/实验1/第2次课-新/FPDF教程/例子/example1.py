#! /usr/bin/env python
#coding=utf-8
from fpdf import FPDF

pdf = FPDF()
pdf.add_page()
pdf.set_font('Arial', 'B', 16)
pdf.cell(40, 10, '<h1>Hello World!<h1>')
pdf.output('tuto1.pdf', 'F')
