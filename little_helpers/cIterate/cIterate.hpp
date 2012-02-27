struct stExtY
{
	float fValue;
	short iCount;
};

struct stParam
{
	float fStart;
	float fEnd;
	float fStepSize;
};

class cInterate
{
	private:
	map<float,stExtY> fWerte;
	unsigned short iParamCount;
	float (*f)(float, float*);
	
	public:
	cInterate(const unsigned short iParamCount, float (*fun)(float, float*));
	bool bReadFile(char* sFilename);
	float* vIterate(unsigned short iParamPos, stParam* param, float& fDiff_min, float* fParamCur, float* fParamMin);
	float* vStartIteration(stParam* param, float* fParamMin, unsigned iNumIter);
};

cInterate::cInterate(const unsigned short iParamCount, float (*fun)(float, float*))
{
	this->iParamCount=iParamCount;
	f=fun;
	fWerte.clear();
}

bool cInterate::bReadFile(char* sFilename)
{
	ifstream hDatei;
	hDatei.open(sFilename);
	if(! hDatei)
	{
		cerr<<"Cannot open file \""<<sFilename<<"\"."<<endl;
		return false;
	}
	fWerte.clear();
	char sBuffer[1024];
	while(hDatei.good())
	{
		hDatei.getline(sBuffer, 1024);
		if(strlen(sBuffer)<=1) continue;
		short i=1; while(i<strlen(sBuffer) && sBuffer[i]!=' ') ++i;
		sBuffer[i]=0;
		float x=atof(sBuffer+1); stExtY y={atof(sBuffer+i+1),1};
		map<float,stExtY>::iterator p=fWerte.find(x);
		if(p == fWerte.end()) fWerte.insert(pair<float,stExtY>(x, y));
		else
		{
			p->second.fValue+=y.fValue;
			p->second.iCount++;
		}
	}
	hDatei.close();
	map<float,stExtY>::iterator p=fWerte.begin();
	while(p!=fWerte.end())
	{
		p->second.fValue /= (float)(p->second.iCount);
		// p->second.iCount=1;
		cout<<(p->first)<<'\t'<<(p->second.fValue)<<endl;
		++p;
	}
	return true;
}

float* cInterate::vIterate(unsigned short iParamPos, stParam* param, float& fDiff_min, float* fParamCur, float* fParamMin)
{
	if(iParamPos==iParamCount)
	{
		float fDiff=0;
		map<float,stExtY>::iterator p=fWerte.begin();
		while(p!=fWerte.end())
		{
			float fAbw=/*fabs(*/ f(p->first, fParamCur) - (p->second.fValue) /*)*/;
			fDiff += fAbw*fAbw;
			++p;
		}
		if(fDiff<fDiff_min)
		{
			fDiff_min=fDiff;
			//cout<<" ( ";
			for(unsigned short i=0; i<iParamCount; ++i) /*{*/fParamMin[i]=fParamCur[i]; /*cout<<fParamMin[i]<<' ';}*/
			//cout<<")"<<endl;
		}
	}
	else
	{
		for(fParamCur[iParamPos]=param[iParamPos].fStart; fParamCur[iParamPos]<=param[iParamPos].fEnd; fParamCur[iParamPos]+=param[iParamPos].fStepSize)
		{
			if(iParamPos==0) cout<<' '<<(100*(fParamCur[iParamPos]-param[iParamPos].fStart)/(param[iParamPos].fEnd-param[iParamPos].fStart))<<'%'<<flush;
			vIterate(iParamPos+1, param, fDiff_min, fParamCur, fParamMin);
		}
		if(iParamPos==0) cout<<endl;
	}
	return fParamMin;
}

float* cInterate::vStartIteration(stParam* param, float* fParamMin, unsigned iNumIter)
{
	float* ff;
	for(unsigned n=0; n<iNumIter; ++n)
	{
		cout<<"Starting Iteration "<<n<<endl;
		float fDiff_min=1E32;
		float fParam[iParamCount];
		ff=vIterate(0, param, fDiff_min, fParam, fParamMin);
		for(unsigned short i=0; i<iParamCount; ++i)
		{
			cout<<"\np"<<i<<" = "<<fParamMin[i];
			param[i].fStart=fParamMin[i]-param[i].fStepSize;
			param[i].fEnd  =fParamMin[i]+param[i].fStepSize;
			param[i].fStepSize/=16.0;
		}
		cout<<endl;
	}
	return ff;
}
