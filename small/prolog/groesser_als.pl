groesser_als([], _, []).
groesser_als([X|L], N, [X|M]) :- X > N, groesser_als(L, N, M).
groesser_als([X|L], N, M) :- not(X > N), groesser_als(L, N, M).
