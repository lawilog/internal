% octave, this is not a "function file", but a "script file":
1;

function y = f(x)
	y = exp(-(x-3).^2);
end

function [g_real, g_imag] = sft(f_real, f_imag, k, x) % simple/stupid/slow FT
	%   f * exp(-i*k*x)
	% = (f_real + i * f_imag) * (cos(k*x) - i * sin(k*x))
	% = (f_real * cos(k*x) + f_imag * sin(k*x))  +  i * (f_imag * cos(k*x) - f_real * sin(k*x))
	Nk = length(k);
	Nx = length(f_real);
	phi = (0:(Nx-1))*2*pi/Nx;
	g_real = zeros(Nk, 1);
	g_imag = zeros(Nk, 1);
	for ki=1:Nk
		kk = k(ki);
		%phi = kk*x;
		g_real(ki) = sum(f_real .* cos(phi) + f_imag .* sin(phi));
		g_imag(ki) = sum(f_imag .* cos(phi) - f_real .* sin(phi));
	end
	g_real = g_real / sqrt(2*pi);
	g_imag = g_imag / sqrt(2*pi);
end


x = linspace(-10, 10, 1000);
k = linspace(-10, 10, 1000);

fvek = f(x);
f_real = real(fvek);
f_imag = imag(fvek);

[g_real, g_imag] = sft(f_real, f_imag, k, x);
Dx = x(2) - x(1);
g_real = g_real * Dx;
g_imag = g_imag * Dx;

%figure; hold on;
plot(x, f_real, 'r',
     x, f_imag, 'm',
     k, g_real, 'b',
     k, g_imag, 'g',
     k, (g_real.^2 + g_imag.^2), 'c'
);
% hold off;
