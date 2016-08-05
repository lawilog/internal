N = 100;
D = zeros(N, N);
k = 0;
while k < 23
    ix = randi(N);
    iy = randi(N);
    if 3 < ix && ix <= N-3 && 3 < iy && iy <= N-3
        k = k + 1;
        D(ix,iy) = 1;

        D(ix-3,iy) = 1;
        D(ix-2,iy) = 1;
        D(ix-1,iy) = 1;
        D(ix+1,iy) = 1;
        D(ix+2,iy) = 1;
        D(ix+3,iy) = 1;
        
        D(ix,iy-3) = 1;
        D(ix,iy-2) = 1;
        D(ix,iy-1) = 1;
        D(ix,iy+1) = 1;
        D(ix,iy+2) = 1;
        D(ix,iy+3) = 1;
    end
end
figure(1); imagesc(D);                                                 title('image');
figure(2); imagesc(autokov2 (D, 8, 8));        colorbar; colormap jet; title('autokov2');
figure(3); imagesc(autokorr2(D, 8, 8));        colorbar; colormap jet; title('autokorr2');
figure(4); imagesc(autokorr2_approx(D, 8, 8)); colorbar; colormap jet; title('autokorr2 approx');
figure(5); imagesc(autokov2_approx(D, 8, 8));  colorbar; colormap jet; title('autokov2 approx');
