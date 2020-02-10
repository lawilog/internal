D = [
1 2 340
2 3 480
3 1 360
3 4 370
2 4 260
4 5 330
3 5 160 # guessed
5 6 380
4 6 480
6 7 270
5 7 445
7 8 380
5 8 390
4 9 280 # 290
6 9 305
6 10 130 # 110
9 10 275
9 11 380
10 11 260
];

T = [
1 2 3
2 4 3
3 4 5
4 6 5
5 6 7
5 7 8
4 9 6
6 9 10
9 11 10
];

function [xc, yc] = tripos(xa, ya, xb, yb, dac, dbc)
  dab = norm([xb-xa; yb-ya]);
  xtmp = dab/2 + (dac^2-dbc^2)/(2*dab);
  ytmp = sqrt(dac^2 - xtmp^2);
  d = [xb-xa, yb-ya];
  d /= norm(d);
  xc = xa + xtmp*d(1) - ytmp*d(2);
  yc = ya + xtmp*d(2) + ytmp*d(1);
end

node = unique(reshape(T, [1, prod(size(T))]));
Nnodes = length(node);
Ntris = rows(T);
M = max(node);

[cii,cjj]=find(sparse(D(:,1), D(:,2), ones(1,rows(D)), M, M) + sparse(D(:,2), D(:,1), ones(1,rows(D)), M, M)==2);
if length(cii) > 0
  for ii=1:length(cii)
    printf("(E) duplicate %i %i\n", cii(ii), cjj(ii));
  end
  error('Specify each length exactly once');
end

d = sparse(D(:,1), D(:,2), D(:,3), M, M) + sparse(D(:,2), D(:,1), D(:,3), M, M);
processed = zeros(1, Ntris);
positioned = 0 * node;
x = zeros(1, Nnodes);
y = zeros(1, Nnodes);

Atot = 0;
for t=1:Ntris
  a = d(node(T(t,1)), node(T(t,2)))+0;
  b = d(node(T(t,2)), node(T(t,3)))+0;
  c = d(node(T(t,3)), node(T(t,1)))+0;
  if a + b < c || a + c < b || b + c < a
    printf("(E) triangle %i does not fulfill triangle inequality\n", t);
    disp(T(t,:));
  end
  s = (a+b+c)/2;
  Atot += sqrt(s*(s-a)*(s-b)*(s-c));
end
Atot

% position first node on (0,0)
x(node(1)) = 0;
y(node(1)) = 0;
positioned(node(1)) = 1;

% position second node on (X,0)
x(node(2)) = d(node(1), node(2));
y(node(2)) = 0;
positioned(node(2)) = 1;

while sum(positioned) != Nnodes
  new_position = 0;
  for t=1:Ntris
    if processed(t) == 1
      continue
    end
    p = [positioned(T(t,1)), positioned(T(t,2)), positioned(T(t,3))];
    s = sum(p);
    if s == 3
      printf("(W) indirecly already positioned all nodes of triangle %i\n", t);
      disp(T(t,:));
      processed(t) = 1;
      continue
    end
    if s == 2
      np = -1;
      if p(1) == 0
        np = 1; ia = 2; ib = 3;
      elseif p(2) == 0
        np = 2; ia = 3; ib = 1;
      else
        np = 3; ia = 1; ib = 2;
      end
      na = node(T(t,ia));
      nb = node(T(t,ib));
      nn = node(T(t,np));
      [nx, ny] = tripos(x(na), y(na), x(nb), y(nb), d(na, nn), d(nb, nn));
      x(nn) = nx;
      y(nn) = ny;
      positioned(nn) = 1;
      processed(t) = 1;
      new_position = 1;
      break
    end
  end
  if new_position == 0
    disp("(E) Could not position anything else");
    break
  end
end

for ii=1:rows(D)
  printf("dist from %i to %i: expected %f, actual %f\n", D(ii,1), D(ii,2), D(ii,3), norm([x(D(ii,1))-x(D(ii,2)); y(D(ii,1))-y(D(ii,2))]));
end

figure(1); plot([0], [0], '.'); hold on
for t=1:Ntris
  plot([x(node(T(t,1))), x(node(T(t,2)))], [y(node(T(t,1))), y(node(T(t,2)))], 'bo-');
  plot([x(node(T(t,1))), x(node(T(t,3)))], [y(node(T(t,1))), y(node(T(t,3)))], 'bo-');
  plot([x(node(T(t,2))), x(node(T(t,3)))], [y(node(T(t,2))), y(node(T(t,3)))], 'bo-');
end
hold off
