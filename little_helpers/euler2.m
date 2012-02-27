% Anfangswerte
dt=0.001;
t=(0 : dt : 2.5*pi);

m=1; k=4; r=2;
x=[1.5]; p=[0];

i=1;
while i*dt<=2.5*pi
%	x=[x,x(i)+p(i)/m*dt];
%	p=[p,p(i)-(k*x(i)+r/m*p(i))*dt];
	
	k1=dt*(p(i)/m);
	k2=dt*(p(i)/m+k1/2);
	k3=dt*(p(i)/m+k2/2);
	k4=dt*(p(i)/m+k3);
	x=[x,x(i)+k1/6.0+k2/3.0+k3/3.0+k4/6.0];
	k1=-dt*(k*x(i)+r/m*p(i));
	k2=-dt*((k*x(i)+r/m*p(i))+k1/2);
	k3=-dt*((k*x(i)+r/m*p(i))+k2/2);
	k4=-dt*((k*x(i)+r/m*p(i))+k3);
	p=[p,p(i)+k1/6.0+k2/3.0+k3/3.0+k4/6.0];

	i=i+1;
end

plot([1.1*min([t,p]),1.1*max([t,p])],[0,0],"0-;;",
	[0,0],[1.1*min(x),1.1*max(x)],"0-;;",
	p,x,"1;x-p;",
	t,x,"2;x(t);");
