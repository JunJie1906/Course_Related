%{
/*constants: LT, LE ...*/
#include <stdio.h>
%}
/*regular expressions*/
delim	[\t \n ]
ws	{delim}+
letter	[A-Za-z]
digit	[0-9]
id	{letter}({letter}|{digit})*
number	{digit}+(\.{digit}+)?(E[+|\-]?{digit}+)?

%%
{ws}	{/*do nothing*/}
while	{printf("keyword-while \n");}
do	{printf("keyword-do \n");}
{id}	{printf("ID: %s\n", yytext);}
\<	{printf("rel: %s \n", yytext);}
\<\=	{printf("rel: %s \n", yytext);}
\<\>	{printf("rel: %s \n", yytext);}
\>	{printf("rel: %s \n", yytext);}
\>\=	{printf("rel: %s \n", yytext);}
=	{printf("assign op: %s\n", yytext);}
%%


