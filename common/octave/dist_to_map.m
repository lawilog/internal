% function r = dist_to_map(D)
% input: symmetric matrix D (n x n) with real distances
% output: 2D coordinates r (n x 2) that approximately recover D distances
% needs fmins function from optim package: pkg load optim;
function r = dist_to_map(D)
	[n,m] = size(D);

	% iteratively place points: new position minmizes distance-error with all previous positions fixed
	r = zeros(n, 2);
	for k=2:n
		kk = k-1;
		d = D(1:kk, k);
		r(k,:) = fmins(@(p) (norm( sqrt( (r(1:kk,1)-p(1)).^2 + (r(1:kk,2)-p(2)).^2 ) - d )), randn(1,2));
	end

	% loop over all points again and fine tune their positions, now with respect to all other positions
	for k=1:n
		d = D(:, k);
		r(k,:) = fmins(@(p) (norm( sqrt( (r(:,1)-p(1)).^2 + (r(:,2)-p(2)).^2 ) - d )), r(k,:));
	end

	% turn and center position cloud so that it is mainly along x-axis
	[A,v] = eig(cov(r));
	if v(1,1) < v(2,2); t=A(:,1); A(:,1)=A(:,2); A(:,2)=t; end % swap if necessary
	rA = r*A;
	rAm = mean(rA);
	r = [rA(:,1)-rAm(1), rA(:,2)-rAm(2)];
end
