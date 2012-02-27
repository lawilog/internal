% Hauptprogramm zum Berechnen der Si PP-Bandstruktur
Constants;

myGrid=Grid();

# k=[0.25, 0.25, 0.25];
# T = KinEnergy(k, myGrid)
# det(T)
# V = PotEnergy(myGrid)
# det(V)
# H = T + V; det(H)
# size(H)
# eig(H)

% Plot_SiPP(100, k_Gamma, k_X, myGrid);
% Plot_SiPP(100, k_U, k_Gamma, myGrid);
% Plot_SiPP(100, k_L, k_Gamma, myGrid);
Plot_SiPP(100, k_X, k_U, myGrid);