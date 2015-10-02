% lattice parameters
a = 1;
A = a*[1.5 sqrt(3)/2; 1.5 -sqrt(3)/2];
B = a*[0 0; -1 0];
Nx = 20;
Ny = 20;

disp('generate positions'); % lattice P, too much positions Q, wanted positions R
tic
P = [reshape(repmat(0:Nx-1, Ny, 1), 1, Nx*Ny); repmat(0:Ny-1, 1, Nx)]' * A;
Q = [ P + repmat(B(1,:), Nx*Ny, 1); P + repmat(B(2,:), Nx*Ny, 1) ];
R = Q( Q(:,2)<10 & Q(:,2)>-10 & Q(:,1)<49 & Q(:,2)>10-1.5*Q(:,1) ,:);
[N,~] = size(R); %N = rows(R);
toc

disp('stupid method to find nearest and next nearst neighbors (search all pairs...)')
tic
t1 = 1;
t2 = 0.5;
rn1 = 1.1*a;
rn2 = 1.8*a;
S = sparse(N, N);
for ii=1:N
	for jj=ii+1:N
		r = norm( R(ii,:) - R(jj,:) );
		if r < rn1
			S(ii,jj) = t1;
			S(jj,ii) = conj(t1);
		elseif r < rn2
			S(ii,jj) = t2;
			S(jj,ii) = conj(t2);
		end
	end
end
toc

% disp('calculate N-1 eigenvectors (sparse)');
% tic
% opts.isreal = 1;
% opts.issym = 1;
% [v,w] = eigs(S, N-1, 'sa', opts);
% toc

disp('calculate N eigenvectors (full)')
tic
[v,w] = eig(full(S));
toc

disp('plot (the for loop will take a minute...)')
tic
figure
hold on
plot(Q(:,1), Q(:,2), 'o',  R(:,1), R(:,2), 'rx')
axis square
for ii=1:N
	for jj=find(S(ii,:))
		if S(ii,jj) == t1
			plot(R([ii jj],1), R([ii jj],2));
		%else
		%	plot(R([ii jj],1), R([ii jj],2), 'g');
		end
	end
end
hold off
toc
