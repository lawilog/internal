#!/usr/bin/awk -f
{
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
	for(i=1; i<=NFmax; ++i) printf("%g ", min[i]); print(" min");
	for(i=1; i<=NFmax; ++i) printf("%g ", max[i]); print(" max");
	for(i=1; i<=NFmax; ++i) printf("%g ", s[i]); print(" sum");
	for(i=1; i<=NFmax; ++i) printf("%g ", s[i]/c[i]); print(" avg");
	for(i=1; i<=NFmax; ++i) printf("%g ", sqrt( (q[i]-s[i]*s[i]/c[i]) / (c[i]-1) )); print(" stddev");
}
