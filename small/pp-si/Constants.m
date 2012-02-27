% Konstanten setzen

% Einheiten & Naturkonstanten
global eV = 1;
global nm = 1;
global kg = 1;
global hbar = 1.05457148E-34/1.602E-19; % in eV s
global me = 5.68562958E-30*kg; % http://www.google.de/search?q=electron+mass+in+eV*s^2/(nm)^2
global ryd = 13.6*eV;

% gitterspezifisch
global a_gitterkonst = 0.5*nm; % http://de.wikipedia.org/wiki/Silizium
global b_basis = (4*pi/a_gitterkonst)*[ [-1,1,1] ; [1,-1,1] ; [1,1,-1] ]; % b1 = 2pi * a1 x a2 / a1*(a2 x a3)
global G_beitrag_hkl = [ [1,1,1] ; [2,2,0] ; [3,1,1] ];
global PP = [-0.21 ; 0.04 ; 0.08 ]*ryd;
global k_Gamma = [0, 0, 0];
global k_X     = [1, 0, 0];
global k_U     = [0.75, 0.75, 0];
global k_L     = [0.5, 0.5, 0.5];

global Emax=200*eV;
global kmax=sqrt(2*me*Emax)/hbar;
b_basis_normen=[norm(b_basis(1,:)), norm(b_basis(2,:)), norm(b_basis(3,:))]
global nmax=ceil(kmax./b_basis_normen); % [5, 5, 5];
global nMatDim=nmax(1)*nmax(2)*nmax(3);
