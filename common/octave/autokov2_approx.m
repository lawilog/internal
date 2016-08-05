% return approximative 2d auto covariance of matrix A within window [0,m] x [0,n]
function C = autokov2_approx(A, m, n)
    [M, N] = size(A);
    A = A - sum(sum(A))/M/N; % substract mean before and then assume that mean will be approx 0 in every subwindow
    C = zeros(m+1, n+1);
    for sx=0:m
        for sy=0:n
            u = A(1:(M-sx), 1:(N-sy));
            v = A((sx+1):end, (sy+1):end);
            L = numel(u); % == numel(v)
            % C(sx+1, sy+1) = sum(sum(u .* v)) / L;
            C(sx+1, sy+1) = sum(sum(u .* v)) / L;
        end
    end
end
