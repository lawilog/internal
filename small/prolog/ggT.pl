% ggT(14,21, G). G = 7 .
ggT(A, 0, A).
ggT(A, B, G) :- R is A mod B, ggT(B, R, G).
