struct stExtY
{
	float fMin;
	float fMax;
};

class cInterate
{
	private:
	map<float,stExtY> fWerte;
	float (*f)(float, float);
	
	public:
	cInterate(const unsigned short iParamCount, float (*fun)(float, float));
	bool bReadFile(char* sFilename);
	void vGetBounds(float* fParamRange, float* fMinMax);
};

cInterate::cInterate(float (*fun)(float, float))
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
		float x=atof(sBuffer+1); float fY=atof(sBuffer+i+1); stExtY y={fY, fY};
		map<float,stExtY>::iterator p=fWerte.find(x);
		if(p == fWerte.end()) fWerte.insert(pair<float,stExtY>(x, y));
		else
		{
			if(y < p->second.fMin) p->second.fMin=y;
			if(y > p->second.fMax) p->second.fMax=y;
		}
	}
	hDatei.close();
	return true;
}

bool cInterate::bIntersects(float fParam)
{
	map<float,stExtY>::iterator p=fWerte.begin();
	while(p!=fWerte.end())
	{
		float y=f(p->first, fParam);
		if(y<p->second.fMin || y>p->second.fMax) return true;
		++p;
	}
	return false;
}

void cInterate::vGetBounds(float* fParamRange, float* fMinMax) //in: [p_min, p_max, p_fit], out: [min, max]
{
	fMinMax[0]=fParamRange[0];
	fMinMax[1]=fParamRange[1];
	float f=fParamRange[2];
	for(unsigned i=0; i<10; ++i)
	{
		float p=(fParamRange[0]+f)/2.0;
		if(bIntersects(p)) fMinMax[0]=p;
		else 
	
}