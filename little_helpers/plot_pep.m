function plot_pep(A)
	% a1=A(1,:); a2=A(2,:); a3=A(:,3);
	
	% b = binary numbers fom 0 to 7 as binary 8x3 array
	b = [0 0 0; 0 0 1; 0 1 0; 0 1 1; 1 0 0; 1 0 1; 1 1 0; 1 1 1]

	figure;
	hold on;
	for i0=1:8
		for i1=1:8
			if sum(b(i0,:)!=b(i1,:)) == 1
				r0 = b(i0,:)*A;
				r1 = b(i1,:)*A;
				plot3([r0(1), r1(1)], [r0(2), r1(2)], [r0(3), r1(3)]);
			end
		end
	end
	hold off;
end

% e001=[0 0 0; 0 0 0; 0 0 -0.1]
% e110=[-0.1 0.1 0; 0.1 -0.1 0; 0 0 0]
% a1=[0 1/2 1/2]; a2=[1/2 0 1/2]; a3=[1/2 1/2 0]; A=[a1; a2; a3]
% A*(eye(3) + e001)
% A*(eye(3) + e110)
