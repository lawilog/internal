1;

% zu minimieren
function z=f(r)
	z = (r(1)-1)^2 + (r(2)-1)^2;
end

% nebenbedingung
function D=g(r)
	D = r(1)^2 + r(2)^2 - 1;
end

[x, obj, info, iter, nf, lambda] = sqp([0, 0], @f, @g)
