% Grid erzeugen
function[myGrid] = Grid()
global Emax kmax nmax nMatDim
Emax
kmax
nmax
myGrid = zeros(nMatDim, 3);
counter = 0;
hkl = (1:3);
for hkl(1) = -nmax(1):nmax(1)
	for hkl(2) = -nmax(2):nmax(2)
		for hkl(3) = -nmax(3):nmax(3)
			k = norm(hkl2k_xyz(hkl));
			if k < kmax
				counter = counter+1;
				myGrid(counter, :) = hkl; % kmax*hkl./nmax;
			end
		end
	end
end
nMatDim = counter;