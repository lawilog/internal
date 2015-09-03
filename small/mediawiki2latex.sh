#!/bin/bash
cat <<EOF
\documentclass[12pt,a4paper]{article}
\usepackage[utf8x]{inputenc}
\usepackage{ucs}
% \usepackage[german]{babel}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\usepackage{soul}
\usepackage{graphicx}
\usepackage{hyperref}
\author{WikiBook Authors}
\begin{document}
EOF

perl -pe "
	s|'''(.*)'''|\\\\textbf{\1}|g;
	s|''(.*)''|\\\\textit{\1}|g;
	"'
	s#{{NumBlk *\| *: *\| *<math>(.*?)</math> *\| *{{EquationRef\|(.*?)}} *}}#\\begin{equation}\\label{eq:\2}\n\1\n\\end{equation}#g;
	s#{{NumBlk *\| *: *\| *{{Equation box 1 .*?\|title *= *(.*?) .*?\|equation *= *<math>(.*?)</math> *}}\|{{EquationRef\|(.*?)}}}}#\\begin{equation}\\label{eq:\3}\n\2\n\\end{equation}#g;
	s#{{EquationNote\|(.*?)}}#\\ref{eq:\1}#g;
	
	s|#|\\#|g;
	s|^== (.*)==$|\\section{\1}|g;
	s|^=== (.*)===$|\\subsection{\1}|g;
	s|^==== (.*)====$|\\subsubsection{\1}|g;
	s|^===== (.*)=====$|\\paragraph{\1}|g;
	s|^====== (.*)======$|\\subparagraph{\1}|g;
	s|<math>(.*?)</math>|\$\1\$|g;
	s|<math>|\\begin{equation*}|g;
	s|</math>|\\end{equation*}|g;
	s|<u>(.*?)</u>|\\underline{\1}|g;
	s|<s>(.*?)</s>|\\st{\1}|g;
	s|<big>(.*?)</big>|\\begin{large}\1\\end{large}|g;
	s|<small>(.*?)</small>|\\begin{scriptsize}\1\\end{scriptsize}|g;
	s|<sup>(.*?)</sup>|\$^{\\text{\1}}\$|g;
	s|<sub>(.*?)</sub>|\$_{\\text{\1}}\$|g;
	s|<ref *name="(.*)" */>||g;
	s|<references />|\\thebibliography |g;
	s|<br *>|\n\n|g;
	s|<br */>|\n\n|g;
	s|^:* ||g;
	s/\[\[File:(.*?)\|(.*?)\|(.*)\]\]/\\includegraphics{\1}/g;
	s/\[\[(.*?)\|(.*?)\]\]/\\href{\1}{\2}/g;
	s/\[\[(.*?)\]\]/\\href{\1}{\1}/g;
	' ${@}

echo '\end{document}'

# 's|^: (.*?)$|\n\\setlength{\\leftskip}{3em}\n\1\n\\setlength{\\leftskip}{0em}\n|g;
# 's|^:: (.*?)$|\n\\setlength{\\leftskip}{6em}\n\1\n\\setlength{\\leftskip}{0em}\n|g;
# {{NumBlk|:|{{Equation box 1 |background colour=whit |title=<u>ℝ<sup>n</sup> → ℝ<sup>m</sup> mapping</u> |equation = <math>...</math>}}|{{EquationRef|3}}}}
 