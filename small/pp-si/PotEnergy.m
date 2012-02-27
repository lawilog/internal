% Potentielle Energie berechnen
function[PotMat] = PotEnergy(myGrid)
global nMatDim a_gitterkonst G_beitrag_hkl PP
PotMat=zeros(nMatDim, nMatDim);
for ii=1:nMatDim
	for jj=ii:nMatDim
		deltaG = myGrid(jj,:)-myGrid(ii,:);
		for n=1:3
			if or(all(sort(deltaG) == sort(G_beitrag_hkl(n,:))), all(sort(-deltaG) == sort(G_beitrag_hkl(n,:))))
				PotMat(ii, jj) = PotMat(jj, ii) = PP(n)*cos(deltaG*[1;1;1]*a_gitterkonst/8);
			end
		end
	end
end
