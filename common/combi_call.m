% combi_call calls callbackfunc with a vector of length n for each of the length(a)^n combinations of elements in a
function combi_call(a, n, callbackfunc)
	m = length(a);
	c = ones(1, n);
	k = 1;
	while k-1 ~= n
		callbackfunc( a(c) )
		k = 1;
		while k <= n
			if ++c(k) <= m
				break
			end
			c(k++) = 1;
		end
	end
end

% e.g.: combi_call([11 22 33], 4, @disp)
