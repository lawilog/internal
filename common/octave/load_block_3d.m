function [data, x, y, z] = load_block_3d(filepath)

	B = sortrows(load(filepath), [1,2,3]);
	x = unique(B(:,1));
	y = unique(B(:,2));
	z = unique(B(:,3));
	
	[nxyz, m] = size(B);
	nx = length(x);
	ny = length(y);
	nz = length(z);
	if nx * ny * nz ~= nxyz
		printf('ERROR: Found %i rows, but dims are %i by %i by %i\n', nxyz, nx, ny, nz);
		error('ERROR: Data is not on grid.');
	endif
	
	if m == 4
		data = zeros(nx, ny, nz);
	else
		data = zeros(nx, ny, nz, m-3);
	end
	
	id = 1;
	for ix = 1:nx
		for iy = 1:ny
			for iz = 1:nz
				data(ix, iy, iz, :) = B(id, 4:m);
				id = id + 1;
			end
		end
	end
	
end
