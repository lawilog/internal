% define sum: sum([10,5,1], n). N = 16.
sum([K|L], S) :- sum_to(L, S, K).
sum_to([], K, K).
sum_to([K|L], S, Temp) :- NewTemp is Temp + K, sum_to(L, S, NewTemp).

% define enum1: enum1([4,3,2,1]). true.
enum1([1]).
enum1([N|R]) :- length(R, M), M is N-1, enum1(R).

% define my_sort

permutation([]).
permutation(Perm) :- sort(Perm, PermSort), reverse(PermSort, PermSortR), enum1(PermSortR).


magisches_quadrat(Rows, N) :- length(Rows, N),
                              N2 is N * N,
                              flatten(Rows, RowsFlat),
                              length(RowsFlat, N2),
                              permutation(RowsFlat),
                              NeededSum is (N * N * N + N) / 2,
                              row_sums(Rows, NeededSum).

row_sums([], _).
row_sums([Row|L], NeededSum) :- sum(Row, NeededSum), row_sums(L, NeededSum).


