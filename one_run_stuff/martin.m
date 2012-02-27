##Coulombkraefte in einer geladenen Hohlkugel
##Martin Kunz, 3.2.2008
disp("______________________________________________________")
disp("Berechnet die Kraft auf eine Ladung in einer Hohlkugel")
##Ladungen verteilen
tic();                                   #Timer starten
NP=10000

punkte=zeros(NP,3);                      #x,y,z
i=1;
do
  theta=rand*pi();                       #Polarwinkel
  sinth=sin(theta);
  if rand>1-sinth                        #Gleichverteilung sicherstellen
    phi=rand*2*pi();                     #Azimut
    punkte(i,1)=cos(phi)*sinth;
    punkte(i,2)=sin(phi)*sinth;
    punkte(i,3)=cos(theta);
    i++;
  endif
until i==NP+1
toc(),disp("(Zeit für Verteilung der Punkte)")

Fx=[]; Fy=[];
for R=0:0.1:5
	##Bezugspunkt festlegen
	r=[R,R,R];
	
	##Kräfte berechnen und aufaddieren
	tic();
	fges=0;
	
	for j=1:NP
	vec=punkte(j,:)-r;
	fj=vec/(norm(vec))^3;
	fges+=fj;
	endfor
	
	fges
	#disp("Gesamtkraft/Anzahl der Punkte")
	disp(norm(fges)/NP)
	#disp("°°°°°°°°°")
	#toc(),disp("(Zeit für Berechnung der Kraft)");

	Fx=[Fx,R]; Fy=[Fy,norm(fges)/NP];
endfor

plot(Fx,Fy);
#if NP<=1000
#  plot3(punkte(:,1),punkte(:,2),punkte(:,3),"o",r(1),r(2),r(3),"*");
#else
#  plot(punkte(:,3),punkte(:,1),".",r(3),r(1),"*");
#endif
