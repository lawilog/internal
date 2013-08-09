% function combi_call(a, n, callbackfunc)
% calls callbackfunc with a vector of length n for each of the length(a)^n combinations of elements in a
% e.g.: combi_call([11 22 33], 4, @disp)
function combi_call(a, n, callbackfunc)
	m = length(a);
	c = ones(1, n);
	k = 1;
	while k-1 ~= n
		callbackfunc( a(c) )
		k = 1;
		while k <= n
			c(k) = c(k) + 1;
			if c(k) <= m
				break
			end
			c(k) = 1;
			k = k + 1;
		end
	end
end
