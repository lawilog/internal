sum_to([K|L], S) :- sum_toB(L, S, K).
sum_toB([], K, K).
sum_toB([K|L], S, Akku) :- AkkuNeu is Akku + K, sum_toB(L, S, AkkuNeu).