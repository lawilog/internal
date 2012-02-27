% ausgleichsgerade y=a*x+b

x=[-1; 0; 2; 3];
y=[ 0; 1; 2; 5];

C = [x.^0, x.^1]
A = C'*C
b = C'*y
n_m = A^-1 * b
