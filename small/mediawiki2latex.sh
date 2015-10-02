#!/bin/bash
cat <<EOF
\documentclass[12pt,a4paper]{article}
\usepackage[utf8x]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{lmodern}
\usepackage{ucs}
% \usepackage[german]{babel}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{soul}
\usepackage{graphicx}
%\usepackage{enumerate}
\usepackage{titling}
\author{Several Wiki Authors}
\title{My Article}
\usepackage[pdftex,pagebackref,pdfusetitle,colorlinks=true]{hyperref}
\hypersetup{allcolors=[rgb]{0.33,0,0}}
\setlength{\parindent}{0pt}

\begin{document}
\begin{center}{\LARGE\textbf{\thetitle}}\end{center}
EOF

(echo; cat ${@}) | awk 'BEGIN{enum=0; list=0};
!/^#/ { if(enum) {enum=0; print "\\end{enumerate}"}; }
!/^\*/{ if(list) {list=0; print "\\end{itemize}"};   }
/^#/{
	if(! enum) {enum=1; print "\\begin{enumerate}";}
	sub(/^#/, "\\item ");
}
/^\*/{
	if(! list) {list=1; print "\\begin{itemize}";}
	sub(/^\*/, "\\item ");
}
1
END{
	if(enum) print "\\end{enumerate}\n"
	if(list) print "\\end{itemize}\n"
}' | perl -pe "undef $/;
s|'''(.*)'''|\\\\textbf{\1}|g;
s|''(.*)''|\\\\textit{\1}|g;
"'
s@{{NumBlk *\| *: *\| *{{Equation box 1 [^}]*?\|title *= *([^\|]*?)\|equation *= *<math>(.*?)</math> *}}\|{{EquationRef\|(.*?)}}}}@\\begin{equation}\\label{eq:\3}
	\\boxed{\\begin{gathered}
	\\text{\1}\\\\
	\2
	\\end{gathered}}
\\end{equation}@sg;
s@{{NumBlk *\| *: *\| *{{Equation box 1 [^}]*?\|equation *= *<math>(.*?)</math> *}}\|{{EquationRef\|(.*?)}}}}@\\begin{equation}\\label{eq:\2}
	\\boxed{\1}
\\end{equation}@sg;
s@{{Equation box 1 [^}]*?\|title *= *([^\|]*?)\|equation *= *<math>(.*?)</math> *}}@\\begin{equation*}
	\\boxed{\\begin{gathered}
	\\text{\1}\\\\
	\2
	\\end{gathered}}
\\end{equation*}@sg;
s@{{Equation box 1 [^}]*?\|equation *= *<math>(.*?)</math> *}}@\\begin{equation*}
	\\boxed{\1}
\\end{equation*}@sg;
s@{{NumBlk *\| *: *\| *<math>(.*?)</math> *\| *{{EquationRef\|(.*?)}} *}}@
\\begin{equation}\\label{eq:\2}
	\1
\\end{equation}@sg;
s@{{EquationNote\|(.*?)}}@(\\ref{eq:\1})@sg;

s@\[\[#(.*?)\|(.*?)\]\]@\\hyperref[sec:\1]{\2}@sg;
s@\[\[#(.*?)\]\]@\\hyperref[sec:\1]{\1}@sg;
s@\[\[w:(.*?)\|(.*?)\]\]@\\href{https://en.wikipedia.org/wiki/\1}{\2}@sg;
s@\[\[w:(.*?)\]\]@\\href{https://en.wikipedia.org/wiki/\1}{\1}@sg;
s@\[\[b:(.*?)\|(.*?)\]\]@\\href{https://en.wikibooks.org/wiki/\1}{\2}@sg;
s@\[\[b:(.*?)\]\]@\\href{https://en.wikibooks.org/wiki/\1}{\1}@sg;
s@\[\[wikt:(.*?)\|(.*?)\]\]@\\href{https://en.wiktionary.org/wiki/\1}{\2}@sg;
s@\[\[wikt:(.*?)\]\]@\\href{https://en.wiktionary.org/wiki/\1}{\1}@sg;
s@\[\[(.*?)\|(.*?)\]\]@\\href{https://en.wikipedia.org/wiki/\1}{\2}@sg;
s@\[\[(.*?)\]\]@\\href{https://en.wikipedia.org/wiki/\1}{\1}@sg;

s|#|\\#|g;
s|%|\\%|g;
s|^== (.*) ==$|\\section{\1}\\label{sec:\1}|mg;
s|^=== (.*) ===$|\\subsection{\1}\\label{sec:\1}|mg;
s|^==== (.*) ====$|\\subsubsection{\1}\\label{sec:\1}|mg;
s|^===== (.*) =====$|\\paragraph{\1}\\label{sec:\1}|mg;
s|^====== (.*) ======$|\\subparagraph{\1}\\label{sec:\1}|mg;
s|<math>(.*?)</math>|\$\1\$|sg;
s|<u>(.*?)</u>|\\underline{\1}|sg;
s|<s>(.*?)</s>|\\st{\1}|sg;
s|<big>(.*?)</big>|\\begin{large}\1\\end{large}|sg;
s|<small>(.*?)</small>|\\begin{scriptsize}\1\\end{scriptsize}|sg;
s|<sup>(.*?)</sup>|\$^{\\text{\1}}\$|sg;
s|<sub>(.*?)</sub>|\$_{\\text{\1}}\$|sg;
s|<ref *name="(.*)" */>|\\cite{\1}|g;
s|<references />|\\thebibliography |g;
s|<br *>|\n\n|g;
s|<br */>|\n\n|g;
s|^: |\\hspace{1em} |mg;
s|^:: |\\hspace{2em} |mg;
s|^::: |\\hspace{3em} |mg;
s|^:::: |\\hspace{4em} |mg;
s|^::::: |\\hspace{5em} |mg;
s|^:::::: |\\hspace{6em} |mg;
s/\[\[File:(.*?)\|(.*?)\|(.*)\]\]/\\includegraphics{\1}/sg;
'

cat <<EOF

\noindent\hrulefill

{\footnotesize Latest version of this article online on: \href{https://en.wikibooks.org/}{https://en.wikibooks.org/}

Authors / Contributors: Lars Winterfeld

Licence: \href{https://creativecommons.org/licenses/by-sa/3.0/}{Creative Commons Attribution-Share Alike 3.0}}
\end{document}
EOF

# s|^:* ||mg;
# s|^: (.*?)$|\n\\setlength{\\leftskip}{3em}\n\1\n\\setlength{\\leftskip}{0em}\n|mg;
# s|^:: (.*?)$|\n\\setlength{\\leftskip}{6em}\n\1\n\\setlength{\\leftskip}{0em}\n|mg;
# s|<math>|\\begin{equation*}|g;
# s|</math>|\\end{equation*}|g;
# {{NumBlk|:|{{Equation box 1 |background colour=whit |title=<u>ℝ<sup>n</sup> → ℝ<sup>m</sup> mapping</u> |equation = <math>...</math>}}|{{EquationRef|3}}}}
 