% regression E(B)=B*c

E = [1.72965E-024; 1.80239E-024; 1.45179E-024; 2.07773E-024; 1.57867E-024; 1.51764E-024; 2.14915E-024; 2.30849E-024; 2.47522E-024; 3.04289E-024; 3.97426E-024; 3.78714E-024; 3.09998E-024; 4.12181E-024; 3.94369E-024; 4.20171E-024; 4.09875E-024; 4.36173E-024; 4.46022E-024; 4.35878E-024; 4.65875E-024; 5.02913E-024; 4.85273E-024; 5.16967E-024; 4.73776E-024; 4.87674E-024; 5.29645E-024; 5.43013E-024];
B = -1.*[262.67; 279.67; 297; 311.33; 330.67; 347.33; 363.33; 381; 397; 415.33; 430.33; 447.67; 465.33; 481.67; 497; 512; 527.67; 542; 559; 574.67; 590.33; 604.67; 617.67; 633; 645.67; 656; 668; 678];
dE = [6.02573E-028; 5.14600E-028; 3.13014E-028; 5.35585E-028; 4.42230E-028; 3.70479E-028; 4.23470E-028; 4.34994E-028; 4.30136E-028; 5.74912E-028; 7.23641E-028; 7.55198E-028; 5.07266E-028; 8.55748E-028; 7.37953E-028; 7.96384E-028; 6.34991E-028; 8.18090E-028; 8.47095E-028; 8.03986E-028; 7.17621E-028; 8.34713E-028; 7.42135E-028; 8.38143E-028; 6.92662E-028; 7.01186E-028; 8.15572E-028; 8.78251E-028];

A = B'*B;
b = B'*E;

x = -1.* (A^-1 * b)
dx = abs( A^-1 * (abs(B') * dE))