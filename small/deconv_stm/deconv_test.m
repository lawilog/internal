step=0.1;
x=0:step:100;
% x./10 + 
m = 0.8 ./ ( exp(-x+50) + 1 );
m = m + exp(-(x-20).*(x-20)/40);
m = m + 0.1.*exp(-(x-80).*(x-80)/20);
% plot(x,m);

sx=0:1:10;
sy=exp(-(sx-5).*(sx-5));
co=conv(m,sy);
n=ceil(length(sx)/2);
plot(x',[m',co(n:length(co)-n+1)']);
