%{
#include "stdio.h"
%}

%%
(a|b)*ab                     printf("Pattern (a|b)*ab matched: %s\n",yytext);
(00|11|(01|10)(00|11)*(01|10))*  printf("Pattern: even_num_0_1: %s\n", yytext);
z{2,4}[^z\n]*                       printf("Pattern fix freq matched: %s\n", yytext);
(.*)                         printf("Pattern not matched: %s\n", yytext);
%%


\begin{frame}{Gated Recurrent Unit (GRU)}
GRU是LSTM的一种轻量实现.
\begin{center}
\includegraphics[width=4.0in]{lstm}
\end{center}
\end{frame}

\begin{frame}{Gated Recurrent Unit (GRU)}
\begin{columns}[T]
\begin{column}{0.7\textwidth}
\begin{center}
GRU是LSTM的一种轻量实现.
\begin{center}
\includegraphics[width=2.0in]{lstm}
\end{center}
\end{column}
\begin{column}{0.3\textwidth}
\begin{itemize}
\item $z^t = \sigma\left(W_z\cdot\left[h^{t-1}, x^t\right] + b_z\right)$
\vspace{0.2cm}
\item $r^t = \sigma\left(W_r\cdot\left[h^{t-1}, x^t\right] + b_r\right)$
\vspace{0.2cm}
\item $\tilde{h}^t = \tanh\left(W\cdot\left[r^t\circ h^{t-1}, x^t\right] + b_h\right)$
\vspace{0.2cm}
\item $h^t = \left(1 - z^t\right)\circ h^{t-1} + z^t\circ \tilde{h}^t$
\end{column}
\end{columns}
\end{frame}