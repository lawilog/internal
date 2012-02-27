sum_to([], 0).
sum_to([K|L], S) :- sum_to(L, R), S is K+R.
