N=300; y=zeros(1,N); y(1:4)=rand(1,4); for k=5:N; y(k) = 0.6*y(k-4) - 0.1*y(k-3) - 0.1*y(k-2) + 0.2*y(k-1) + 0.1 * randn(); end; figure(1); plot(y, 'o-')

L=30; figure(2); plot(0:L, autocorr(y, L), 'o-');

figure(3); plot(abs(fftshift(fft(y))));

figure(4); X=xcorr(y, L); a=X((L+1):end); plot(0:L, a/(norm(y)^2), 'o-');
