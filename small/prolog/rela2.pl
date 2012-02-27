besser(nichts, ewige_glueckseligkeit).
besser(butterbrot, nichts).
besser(mahlzeit, butterbrot).
besser(restaurant, mahlzeit).
besser(X, Y) :- besser(X, Z), besser(Z, Y).
