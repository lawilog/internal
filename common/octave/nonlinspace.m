% function nonlinspace(a, b, N, f)
% works like linspace(a,b,N), but with non-linear spacing acording to function f,
% which is evaulted in [0, 1], e.g.:
% nonlinspace(2, 3, 10, @exp)
% nonlinspace(0, 100, 11, @(x)(x.^2))
% If f is a linear function, result will be the same as linspace.

function v = nonlinspace(a, b, N, f)
	v = a + (b-a)/(f(1)-f(0)) * (f(linspace(0, 1, N))-f(0));
end
