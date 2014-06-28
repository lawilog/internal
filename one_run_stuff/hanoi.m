1;

function hanoi(N, x, y)
	if N == 1
		disp(sprintf('von %i nach %i', x, y));
	else
		z = 6 - x - y;
		hanoi(N-1, x, z);
		hanoi(1, x, y);
		hanoi(N-1, z, y);
	end
end

hanoi(3, 1, 2);
