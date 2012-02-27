#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//short md_init(const unsigned iNumPart, double* &x, double* &v, double &dBoxX, double &dBoxY);

short md_init(const unsigned iNumPart, double* x, double* v, double dBoxX, double dBoxY)
{
	if(iNumPart==0)
	{
		printf("please supply a valied number of particles\n");
		return 0;
	}
	srand(time(0));
	dBoxX=120;
	dBoxY=120;
	x=(double*) malloc(sizeof(double)*2*iNumPart);
	for(unsigned i=0; i<iNumPart; ++i)
	{
		x[2*i]   = 1.15*((int)iNumPart/10);
		x[2*i+1] = 1.15*((int)iNumPart%10);
	}
	v=(double*) malloc(sizeof(double)*2*iNumPart);
	for(unsigned i=0; i<iNumPart; ++i)
	{
		v[2*i]   = rand()/((double)RAND_MAX);
		v[2*i+1] = rand()/((double)RAND_MAX);
	}
	return 1;
}

short md_read(const char* sFilename, unsigned &iNumPart, double* &x, double* &v, double &dBoxX, double &dBoxY)
{
	FILE* fp=fopen(sFilename, "r");
	if(! fp)
	{
		printf("error: Could not open file \"%s\" for reading.\n". sFilename);
		return 0;
	}
	fscanf(fp, "%u\t%lf\t%lf\n", &iNumPart, &dBoxX, &dBoxY);
	x=(double*) malloc(sizeof(double)*2*iNumPart);
	v=(double*) malloc(sizeof(double)*2*iNumPart);
	unsigned i=0;
	while(! feof(fp) && i<iNumPart)
	{
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &(x[2*i]), &(x[2*i+1]), &(v[2*i]), &(v[2*i+1]));
		++i;
	}
	fclose(fp);
	if(i!=iNumPart)
	{
		printf("error: file corrupted. found %u coordinates, but promissed %u\n", i, iNumPart);
		return 0;
	}
	else return 1;
	
}

double F(double Ax, double Ay, double Bx, double By, double &dBoxX, double &dBoxY)
{
	return 0;
}

short md_run(const unsigned iTimeSteps, const unsigned iNumPart, double* &x, double* &v, double &dBoxX, double &dBoxY)
{
	;
	return 1;
}

short md_write(const char* sFilename, unsigned iNumPart, double* &x, double* &v, double dBoxX, double dBoxY)
{
	FILE* fp=fopen(sFilename, "w");
	if(! fp)
	{
		printf("error: Could not open file \"%s\" for writing.\n". sFilename);
		return 0;
	}
	fprintf(fp, "%u\t%lf\t%lf\n", iNumPart, dBoxX, dBoxY);
	for(unsigned i=0; i<iNumPart; ++i)
	{
		fprintf(fp, "%lf\t%lf\t%lf\t%lf\n", x[2*i], x[2*i+1], v[2*i], v[2*i+1]);
	}
	fclose(fp);
	return 1;
}

void md_cleanup(double* &x, double* &v)
{
	free(v);
	free(x);
}

int main (int argc, char** argv)
{
	if(argc<=2)
	{
		printf("usage:\n"
			"%s i number_of_particles\n"
			"%s c dump_file.dat\n"
			"i = init.\n"
			"c = continue\n"
		, argv[0], argv[0]);
		return 0;
	}
	double* x;
	double* v;
	unsigned iNumPart;
	double dBoxX;
	double dBoxY;
	if(strcmp(argv[1], 'i')==0)
	{
		iNumPart=atoi(argv[2]);
		if(md_init(iNumPart, x, v, dBoxX, dBoxY)==0) return 1;
	}
	else
	{
		if(md_read(argv[2], iNumPart, x, v, dBoxX, dBoxY)==0) return 1;
	}
	md_run(1000, x, v, dBoxX, dBoxY);
	md_write("md.dumb", iNumPart, x, v, dBoxX, dBoxY);
	md_cleanup(x, v);
	return 0;
}
