#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IND(N, i, j) ((i)*(N)+(j))
#define LW_MEM_CHECK(var)					\
({											\
	if(var==0)								\
{										\
		printf("error: got no memory\n");	\
		return 1;							\
}										\
})

void vExplode(const char* sLine, double* dArray, unsigned iItemsOnLine) // double dF[iItemsOnLine];
{
	char sBuffer[128];
	short iPos=0;
	char* c=(char*)sLine;
	unsigned i=0;
	while(1)
	{
		if(*c==0) break;
		if(*c=='\t' || *c=='\n')
		{
			sBuffer[iPos]=0;
			iPos=0;
			if(i<iItemsOnLine) dArray[i]=atof(sBuffer);
			else {printf("error: too many items on line\n"); break;}
			++i;
		}
		else
		{
			sBuffer[iPos]=*c;
			++iPos;
		}
		++c;
	}
}

int main()
{
	char sFilename[]="test.dat";
	const unsigned iLineLen=1024;
	char sLine[iLineLen];
	FILE* fp=fopen(sFilename, "r");
	if(! fp) {printf("error: could not open file \"%s\" for reading\n", sFilename); return 1;}
	if(feof(fp)) {printf("error: to few lines in file\n"); return 1;}
	fgets(sLine, iLineLen, fp);
	unsigned iItemsOnLine=0;
	char* c=sLine;
	while(*c!=0)
	{
		if(*c=='\t' || *c=='\n') ++iItemsOnLine;
		++c;
	}
	printf("%u items per line\n", iItemsOnLine);
	
	double* dArray=(double*) malloc(sizeof(double)*iItemsOnLine);
	LW_MEM_CHECK(dArray);

	while(1)
	{
		vExplode(sLine, dArray, iItemsOnLine);
		printf("[");
		for(unsigned i=0; i<iItemsOnLine; ++i)
		{
			printf("\t%lf", dArray[i]);
		}
		printf("\t]\n");
		if(feof(fp)) break;
		fgets(sLine, iLineLen, fp);
		if(sLine[0]==0) continue;
	}
	printf("done.\n");
	
	free(dArray);
	fclose(fp);
	return 0;
}
