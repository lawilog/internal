function [A] = flaeche(polygon_x, polygon_y)
% Berechnet die Flaeche des Polygons
% polygon_x sind die x-Koordinaten der Punkte
% polygon_y sind die y-Koordinaten der Punkte

A=0;
n=length(polygon_y);
for i=0:1:n-1
	A=A+polygon_y(i+1)*(polygon_x(mod(i-1+n,n)+1)-polygon_x(mod(i+1+n,n)+1));
end
A=A/2;
