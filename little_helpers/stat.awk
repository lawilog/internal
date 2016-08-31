#!/usr/bin/awk -f
!/^#/{
	if(NF>NFmax)
	{
		for(i=NFmax+1; i<=NF; ++i)
		{
			min[i] = $i;
			max[i] = $i;
		}
		NFmax=NF;
	}
	for(i=1; i<=NF; ++i)
	{
		++c[i];
		s[i] += $i;
		q[i] += $i * $i;
		if($i < min[i]) min[i] = $i;
		if($i > max[i]) max[i] = $i;
	}
}
END {
	for(i=1; i<=NFmax; ++i) printf("%g\t", min[i]); print("\tmin");
	for(i=1; i<=NFmax; ++i) printf("%g\t", max[i]); print("\tmax");
	for(i=1; i<=NFmax; ++i) printf("%g\t", s[i]); print("\tsum");
	for(i=1; i<=NFmax; ++i) printf("%g\t", s[i]/c[i]); print("\tavg");
	for(i=1; i<=NFmax; ++i) d[i] = (q[i]-s[i]*s[i]/c[i] < 1e-12) ? 0 : sqrt( (q[i]-s[i]*s[i]/c[i]) / (c[i]-1) );
	for(i=1; i<=NFmax; ++i) printf("%g\t", d[i]); print("\tstddev");
	for(i=1; i<=NFmax; ++i) printf("%g\t", 100*d[i] / (s[i]/c[i]<0? -s[i]/c[i] : s[i]/c[i])); print("\tStddevProcent");
}
