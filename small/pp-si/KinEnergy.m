% Kinetische Energie berechnen
function[KinMat] = KinEnergy(k, myGrid)
global hbar me nMatDim
KinMat = zeros(nMatDim, nMatDim);
for ii = 1:nMatDim
	kG = hkl2k_xyz(k + myGrid(ii,:));
	KinMat(ii, ii) = kG*kG';
end
KinMat = hbar^2/(2*me) * KinMat;
