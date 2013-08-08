n=100;
x=linspace(-2,2,n);
L=diag(-2*ones(1,n)) + diag(ones(1,n-1),-1) + diag(ones(1,n-1),1);
V=1*diag(x.^2);
H=-L+V;
[Psi,E]=eig(H);
plot(x,Psi(:,1), x,Psi(:,2), x,Psi(:,3))
