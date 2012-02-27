#include <cmath>
#include <strstream>
#include <string>

#define MATRIX_TYPE float
#include "my_matrix.h"

struct stExtY
{
	float fValue;
	short iCount;
};

struct stXY
{
	stExtY x;
	stExtY y;
};

class cInterate
{
	private:
	map<float,stExtY> fWerte;
	map<float,stExtY> fWerte_bak;
	
	public:
	cInterate();
	bool bReadFile(char* sFilename);
	bool bWriteFile(char* sFilename);
	void vBackupWerte();
	void vFeatureExtraction();
	void vFeatureExtraction2();
	void vIntegriere();
	void vPunkteHomogenisieren();
};

cInterate::cInterate()
{
	fWerte.clear();
	fWerte_bak.clear();
}

void cInterate::vBackupWerte()
{
	fWerte_bak=fWerte;
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
		short i=1; while(i<strlen(sBuffer) && sBuffer[i]!='\t') ++i;
		sBuffer[i]=0;
		float x=atof(sBuffer); stExtY y={atof(sBuffer+i+1),1};
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
		p->second.iCount=1;
		// cout<<(p->first)<<'\t'<<(p->second.fValue)<<endl;
		++p;
	}
	// cout<<fWerte.size()<<" points read"<<endl;
	return true;
}

bool cInterate::bWriteFile(char* sFilename)
{
	ofstream hDatei;
	hDatei.open(sFilename);
	if(! hDatei)
	{
		cerr<<"Cannot open file \""<<sFilename<<"\"."<<endl;
		return false;
	}
	map<float,stExtY>::iterator p=fWerte.begin();
	while(p!=fWerte.end())
	{
		hDatei << (p->first) << '\t' << (p->second.fValue) << '\n';
		++p;
	}
	hDatei.close();
}

void cInterate::vFeatureExtraction()
{
	const short N=5;
	map<float,stExtY>::iterator p=fWerte.begin();
	if(p==fWerte.end()) {cout<<"error: no data avaliable for feature extraction"<<endl; return;}
	float fAnfangX[N]; float fAnfangY[N]; short n=0;
	while(p!=fWerte.end())
	{
		if(n>=N) break;
		if(p->first > 0 && p->second.fValue > 0)
		{
			fAnfangX[n]=p->first;
			fAnfangY[n]=p->second.fValue;
			++n;
		}
		++p;
	}
	cout<<"\nmu_i"<<endl;
	// cout<<"\nx\ty"<<endl;
	char sBuffer2[10240];
	ostrstream toOctave2(sBuffer2, 10240);
	toOctave2<<"echo \"x=[";
	for(short i=0; i<N; ++i)
	{
		// cout<<fAnfangX[i]<<'\t'<<fAnfangY[i]<<endl;
		toOctave2<<(i==0?"":";")<<fAnfangX[i];
	}
	toOctave2<<"]; y=[";
	for(short i=0; i<N; ++i) toOctave2<<(i==0?"":";")<<fAnfangY[i];
	toOctave2<<"]; C = [x.^0, x.^1]; A = C'*C; b = C'*y; n_m = A^-1 * b\" | octave -q";
	
	system(sBuffer2);
	
	p=fWerte.begin();
	map<float,stExtY>::iterator pMin=p;
	const float fZiel=5E4;
	const short N1=3;
	float fMinDiff=fabs(fZiel-(p->first));
	unsigned iPos=0, iMinPos=0;
	++p;
	while(p!=fWerte.end())
	{
		if(fabs(fZiel-(p->first)) < fMinDiff)
		{
			fMinDiff=fabs(fZiel-(p->first));
			pMin=p;
			iMinPos=iPos;
		}
		++p; ++iPos;
	}
	if(iMinPos<=N1 || iMinPos+N1>=iPos)
	{
		cout<<"error: found pos to close to border"<<endl;
		return;
	}
	else
	{
		// cout<<"\n\nmu_d ... make a regression over these points (and divide my mu_0):\nx\ty"<<endl;
		cout<<"\nmu_d"<<endl;
		for(short i=0; i<N1; ++i) --pMin;
		map<float,stExtY>::iterator pMinMerk=pMin;
		char sBuffer[10240];
		ostrstream toOctave(sBuffer, 10240);
		toOctave<<"echo \"x=[";
		for(short i=0; i<=2*N1; ++i, ++pMin)
		{
			// cout << (pMin->first) << '\t' << (pMin->second.fValue) << endl;
			toOctave<<(i==0?"":";")<<(pMin->first);
		}
		toOctave<<"]; y=[";
		pMin=pMinMerk;
		for(short i=0; i<=2*N1; ++i, ++pMin) toOctave<<(i==0?"":";")<<(pMin->second.fValue);
		toOctave<<"]; C = [x.^0, x.^1]; A = C'*C; b = C'*y; n_m = A^-1 * b\" | octave -q";
		
		system(sBuffer);
	}
	
	map<float,stExtY>::reverse_iterator letz=fWerte.rbegin();
	//cout<<"\n\nMaximum "<<(letz->first)<<" , "<<(letz->second.fValue)<<"\n";
	cout<<"mu_a = "<<(letz->second.fValue / (4E-7*M_PI*(letz->first)))<<endl;
}

void cInterate::vFeatureExtraction2()
{
	map<float,stExtY>::iterator p=fWerte.begin();
	if(p==fWerte.end()) {cout<<"error: no data avaliable for feature extraction"<<endl; return;}
	const short N1=3;
	map<float,stExtY>::iterator pMin[2]={p,p};//[0]=H, [1]=B
	float fMinDiffH0=fabs(p->first);
	float fMinDiffB0=fabs(p->second.fValue);
	unsigned iPos=0, iMinH0Pos=0, iMinB0Pos=0;
	++p;
	while(p!=fWerte.end())
	{
		if(fabs(p->first) < fMinDiffH0)
		{
			fMinDiffH0=fabs(p->first);
			pMin[0]=p;
			iMinH0Pos=iPos;
		}
		if(fabs(p->second.fValue) < fMinDiffB0)
		{
			fMinDiffB0=fabs(p->second.fValue);
			pMin[1]=p;
			iMinB0Pos=iPos;
		}
		++p; ++iPos;
	}
	if(iMinH0Pos<=N1 || iMinH0Pos+N1>=iPos || iMinB0Pos<=N1 || iMinB0Pos+N1>=iPos)
	{
		cout<<"error: found pos to close to border (iMinH0Pos = "<<iMinH0Pos<<" , iMinB0Pos = "<<iMinB0Pos<<")"<<endl;
		return;
	}
	else
	{
		float HB0[2];
		for(short j=0; j<2; ++j)
		{
			Matrix x(2*N1+1, 1);
			Matrix y(2*N1+1, 1);
			Matrix C(2*N1+1, 2);
			Matrix CT(2, 2*N1+1);
			
			for(short i=0; i<N1; ++i) --pMin[j];
			for(short i=0; i<=2*N1; ++i, ++pMin[j])
			{
				// cout << (pMin->first) << '\t' << (pMin->second.fValue) << endl;
				x(i,0)=pMin[j]->first;
				y(i,0)=pMin[j]->second.fValue;
				C(i,0)=CT(0,i)=1;
				C(i,1)=CT(1,i)=pMin[j]->first;
			}
			/*cout<<"x = ["<<x.ColNo()<<"x"<<x.RowNo()<<"]\n"<<x<< "\n"
				"y = ["<<y.ColNo()<<"x"<<y.RowNo()<<"]\n"<<y<< "\n"
				"C = ["<<C.ColNo()<<"x"<<C.RowNo()<<"]\n"<<C<< "\n"
				"CT = ["<<CT.ColNo()<<"x"<<CT.RowNo()<<"]\n"<<CT<< "\n"<<endl;*/
			Matrix A=CT*C;
			Matrix b=CT*y;
			Matrix nm=A.Solve(b);
			/*cout<<"A = ["<<A.ColNo()<<"x"<<x.RowNo()<<"]\n"<<A<< "\n"
				"b = ["<<b.ColNo()<<"x"<<b.RowNo()<<"]\n"<<b<< "\n"
				"nm = ["<<nm.ColNo()<<"x"<<nm.RowNo()<<"]\n"<<nm<< "\n"<<endl;*/
			HB0[j]=(j==0 ? -nm(0,0)/nm(1,0) : nm(0,0));
		}
		cout<<"H = "<<HB0[0]<<"\nB = "<<HB0[1]<<endl;
	}
}

void cInterate::vIntegriere()
{
	map<float,stExtY>::iterator po, pu, pLast;
	po=fWerte.begin(); pu=fWerte_bak.begin();
	if(po==fWerte.end() || pu==fWerte_bak.end()) {cout<<"error: no data avaliable for feature extraction"<<endl; return;}
	if(po->first < pu->first) fWerte_bak.insert(*po);
	else if(pu->first < po->first) fWerte_bak.insert(*pu);
	
	map<float,stExtY>::reverse_iterator pro, pru;
	pro=fWerte.rbegin(); pru=fWerte_bak.rbegin();
	if(pro->first > pru->first) fWerte_bak.insert(*po);
	else if(pru->first > pro->first) fWerte_bak.insert(*pu);
	
	float fSum=0;
	pLast=po; ++po;
	while(po!=fWerte.end())
	{
		fSum += 0.5 * (po->second.fValue + pLast->second.fValue) * (po->first - pLast->first);
		++po; ++pLast;
	}
	pLast=pu; ++pu;
	while(pu!=fWerte_bak.end())
	{
		fSum -= 0.5 * (pu->second.fValue + pLast->second.fValue) * (pu->first - pLast->first);
		++pu; ++pLast;
	}
	cout << "I = " << fSum << endl;
}

void cInterate::vPunkteHomogenisieren()
{
	float fMin=fWerte.begin()->first;
	float fMax=fWerte.rbegin()->first;
	float fStep=(fMax-fMin)/((float)fWerte.size());
	map<float,stExtY>::iterator p=fWerte.begin();
	if(p==fWerte.end()) {cout<<"error: no data avaliable for homogenisation"<<endl; return;}
	map<unsigned, stXY> mNeueWerte;
	while(p!=fWerte.end())
	{
		unsigned u=(unsigned)((p->first - fMin)/fStep);
		map<unsigned,stXY>::iterator w=mNeueWerte.find(u);
		if(w == mNeueWerte.end())
		{
			stExtY x={p->first, 1}; stXY xy={x, p->second};//y.iCount already set to 1
			mNeueWerte.insert(pair<unsigned,stXY>(u, xy));
		}
		else
		{
			w->second.x.fValue+=p->first;
			w->second.x.iCount++;
			w->second.y.fValue+=p->second.fValue;
			w->second.y.iCount++;
		}
		++p;
	}
	fWerte.clear();
	map<unsigned,stXY>::iterator w=mNeueWerte.begin();
	while(w!=mNeueWerte.end())
	{
		stExtY y={w->second.y.fValue / (float)(w->second.y.iCount), 1};
		fWerte.insert(
			pair<float, stExtY>
			(
				w->second.x.fValue / (float)(w->second.x.iCount),
				y
			)
		);
		++w;
	}
	// cout<<fWerte.size()<<" points left"<<endl;
}
