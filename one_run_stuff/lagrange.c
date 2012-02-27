#include <stdio.h>
#include <stdlib.h>

float fLagrange(float x, int iAnz, float* fX, float* fY)
{
	float fSumme=0;
	for(int i=0; i<iAnz; i++)
	{
		float fProdukt=fY[i];
		for(int k=0; k<iAnz; k++) if(i!=k) fProdukt*=(x-fX[k]);
		for(int k=0; k<iAnz; k++) if(i!=k) fProdukt/=(fX[i]-fX[k]);
		fSumme+=fProdukt;
	}
	return fSumme;
}

int main()
{
	printf("Lagrange-Interpolation fuer Polynom n-ten Gerades\n"
		"n = ");
	int n; scanf("%d", &n);
	
	float* fX=malloc((n+1)*sizeof(float));
	float* fY=malloc((n+1)*sizeof(float));
	printf("Geben Sie %d Punkte (x,y) ein.\n", n+1);
	for(int i=0; i<=n; i++)
	{
		printf("x%d = ", i); scanf("%f", &(fX[i]));
		printf("y%d = ", i); scanf("%f", &(fY[i]));
	}
	
	for(float f=-3.0; f<=3.0; f+=0.5)
	{
		printf("%f\t%f\n", f, fLagrange(f, n+1, fX, fY));
	}
	
	free(fX); free(fY);
	return 0;
}
