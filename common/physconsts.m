% http://physics.nist.gov/cuu/Constants/Table/allascii.txt

installed_packages = pkg('list');
b=0; for p=installed_packages; if strcmp(p{1,1}.name, 'miscellaneous'); b=1; end; end
if b
	pkg load miscellaneous;

	c = physical_constant('speed of light in vacuum')
	h = physical_constant('Planck constant')
	q = physical_constant('elementary charge')
	G = physical_constant('Newtonian constant of gravitation')
	kB = physical_constant('Boltzmann constant')
	NA = physical_constant('Avogadro constant')
	me = physical_constant('electron mass')
	mp = physical_constant('proton mass')
	mn = physical_constant('neutron mass')
	u = physical_constant('unified atomic mass unit')
	alpha = physical_constant('fine-structure constant')
	R = physical_constant('molar gas constant')
	p0 = physical_constant('standard atmosphere')
	aB = physical_constant('Bohr radius')
	ge = physical_constant('electron g factor')
	muB = physical_constant('Bohr magneton')
	RK = physical_constant('von Klitzing constant')
	F = physical_constant('Faraday constant')
	sigma = physical_constant('Stefan-Boltzmann constant')
	eV = physical_constant('electron volt')
	Ha = physical_constant('Hartree energy')
	eps0 = physical_constant('electric constant')
	mu0 = physical_constant('mag. constant')
	Ry = physical_constant('Rydberg constant times hc in J')
else
	c = 299792458
	h = 6.62606957e-34
	q = 1.602176565e-19
	G = 6.67384e-11
	kB = 1.3806488e-23
	NA = 6.02214129e+23
	me = 9.10938291e-31
	mp = 1.672621777e-27
	mn = 1.674927351e-27
	u = 1.660538921e-27
	alpha = 0.0072973525698
	R = 8.3144621
	p0 = 101325
	aB = 5.2917721092e-11
	ge = -2.00231930436153
	muB = 9.27400968e-24
	RK = 25812.8074434
	F = 96485.3365
	sigma = 5.670373e-08
	eV = 1.602176565e-19
	Ha = 4.35974434e-18
	eps0 = 8.85418781762e-12
	mu0 = 4*pi*1e-7
	Ry = 2.179872171e-18
end

