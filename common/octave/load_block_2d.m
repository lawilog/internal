function [data, x, y] = load_block_2d(filepath)

	B = sortrows(load(filepath), [1,2,3]);
	x = unique(B(:,1));
	y = unique(B(:,2));
	
	[nxy, m] = size(B);
	nx = length(x);
	ny = length(y);
	if nx * ny ~= nxy
		printf('ERROR: Found %i rows, but dims are %i by %i\n', nxyz, nx, ny);
		error('ERROR: Data is not on grid.');
	endif
	
	if m == 3
		data = zeros(nx, ny);
	else
		data = zeros(nx, ny, m-3);
	end
	
	id = 1;
	for ix = 1:nx
		for iy = 1:ny
			data(ix, iy, :) = B(id, 3:m);
			id = id + 1;
		end
	end
	
end
