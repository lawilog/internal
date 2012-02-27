permutation([]).
permutation(Perm) :- sort(Perm, PermSort), reverse(PermSort, PermSortR), enumaration1(PermSortR).

enumaration1([1]).
enumaration1([N|R]) :- M is N-1, length(R, M), enumaration1(R).
