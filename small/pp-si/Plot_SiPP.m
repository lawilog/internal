% Ergebnisse der Berechnung plotten
function[] = Plot_SiPP(N, k_A, k_B, myGrid)
global nMatDim
Ek = zeros(N, nMatDim);
k_richtung = k_B - k_A;
for kk = 0:N
	Ek(kk+1, :) = eig(KinEnergy(k_A + k_richtung*kk/N, myGrid) + PotEnergy(myGrid));
end
plotmax=ceil(nMatDim/2)
# save -ascii Ek.dat Ek
plot(Ek(:,1:plotmax));
