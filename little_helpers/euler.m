q1=[pi/4]
p1=[0]
dt=0.01
t=(0:dt:2*pi);
i=1;
while i*dt<=2*pi
	q1=[q1,q1(i)+p1(i)*dt];
	p1=[p1,p1(i)-sin(q1(i))*dt];
	i=i+1;
end

q2=[pi/4]
p2=[0]
dt=0.01
t=(0:dt:2*pi);
i=1;
while i*dt<=2*pi
	k1=dt*(p2(i));
	k2=dt*(p2(i)+k1/2);
	k3=dt*(p2(i)+k2/2);
	k4=dt*(p2(i)+k3);
	q2=[q2,q2(i)+k1/6.0+k2/3.0+k3/3.0+k4/6.0];
	k1=-dt*sin(q2(i));
	k2=-dt*sin(q2(i)+k1/2);
	k3=-dt*sin(q2(i)+k2/2);
	k4=-dt*sin(q2(i)+k3);
	p2=[p2,p2(i)+k1/6.0+k2/3.0+k3/3.0+k4/6.0];
	i=i+1;
end
