% return 2d auto correlation of matrix A within window [0,m] x [0,n]
function C = autokorr2(A, m, n)
    [M, N] = size(A);
    C = zeros(m+1, n+1);
    for sx=0:m
        for sy=0:n
            u = A(1:(M-sx), 1:(N-sy));
            v = A((sx+1):end, (sy+1):end);
            L = numel(u); % == numel(v)
            um = sum(sum(u)) / L;
            vm = sum(sum(v)) / L;
            stdu = sqrt(sum(sum(u.^2))/L - um^2);
            stdv = sqrt(sum(sum(v.^2))/L - vm^2);
            C(sx+1, sy+1) = sum(sum((u-um) .* (v-vm))) / L / stdu / stdv;
        end
    end
end
