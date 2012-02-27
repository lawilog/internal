nat(0).
nat(N) :- nat(M), suc(M, N).
suc(N, 0) :- nat(N), !, fail.
suc(M, N) :- suc(M, X), suc(N, X), !, fail.
suc(_, _).
% suc(M, N) :- N is M + 1 .


