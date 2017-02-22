% rotate by angle a around normal vector n
rotmat = @(a, n) [n(1)*n(1)*(1-cos(a))+cos(a), n(1)*n(2)*(1-cos(a))-n(3)*sin(a), n(1)*n(3)*(1-cos(a)+n(2)*sin(a); n(2)*n(1)*(1-cos(a))+n(3)*sin(a), n(2)*n(2)*(1-cos(a))+cos(a), n(2)*n(3)*(1-cos(a))-n(1)*sin(a); n(3)*n(1)*(1-cos(a))-n(2)*sin(a), n(3)*n(2)*(1-cos(a))+n(1)*sin(a), n(3)*n(3)*(1-cos(a))+cos(a)];
