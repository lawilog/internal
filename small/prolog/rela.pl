kleiner(null, zwei).
kleiner(eins, drei).
kleiner(zwei, drei).
kleiner(eins, vier).
kleiner(vier, zehn).
kleiner(X, Y) :- kleiner(X, Z), kleiner(Z, Y).
