pkg load optim;

a = load('wahlomat_union_spd_gruene_fdp_linke_afd_piraten_diepartei.dat');
a = a.a;
d = zeros(8, 8); for ii=1:8; for jj=1:8; d(ii,jj)=norm(a(:,ii) - a(:,jj)); end; end
r = dist_to_map(d)
namen = {'Union', 'SPD', 'Gruene', 'FDP', 'Linke', 'AfD', 'Piraten', 'Partei'}
scatter(r(:,1), r(:,2), 20, [0 0 0; 1 0 0; 0 1 0; 0.9 0.9 0; 1 0 1; 0 0 1; 0.9 0.6 0; 0.5 0.5 0.5], 'filled');
text(r(:,1)+0.5, r(:,2), namen)
