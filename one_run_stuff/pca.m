% PCA test

% create data
N=100;
a=[1,2,3];
b=[-2, 0, 1];
c=[1,1,1];
s=2*rand(1,N)-1;
t=2*rand(1,N)-1;
M=repmat(c,N,1) + s'*a + t'*b + 0.3*(2*rand(N,3)-1);
plot3(M(:,1), M(:,2), M(:,3),'o');

% process data
m = [mean(M(:,1)), mean(M(:,2)), mean(M(:,3))];
D = M - repmat(m, N, 1);
C = cov(D);
[W, lambda] = eig(C); lambda = diag(lambda);
W, lambda
Y = D*W; % Y=(W'*D')'
plot3(Y(:,1), Y(:,2), Y(:,3), 'o');
axis([-4,4, -4,4, -4,4]);
% sort
[s,ind] = sort(lambda,'descend');
lambda_s = lambda(ind);
W_s = W(:,ind);
