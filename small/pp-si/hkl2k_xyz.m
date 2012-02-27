% hkl2k_xyz
function[k_xyz] = hkl2k_xyz(hkl)
global b_basis
k_xyz = hkl(1)*b_basis(1,:) + hkl(2)*b_basis(2,:) + hkl(3)*b_basis(3,:);