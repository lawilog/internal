// (C) Lars Winterfeld
#include <windows>
#include <fstream>
using namespace std;

struct sMyData
{
	char* sParent;
	char* sChild;
	unsigned iSubLevel;
	bool bInSubOfTSView;
	bool bPhotoButtonFound;
	HWND hWndPhoto;
};

// prototypes
BOOL CALLBACK MyEnumChildProc(HWND, LPARAM);
BOOL CALLBACK MyEnumWindowsProc(HWND, LPARAM);

BOOL CALLBACK MyEnumChildProc(HWND hWndChild, LPARAM lParam)
{
	sMyData* myData=(sMyData*)lParam;
	myData->iSubLevel++;
	MyEnumWindowsProc(hWndChild, lParam);// um Rekursion zu verstehen, muss man zunaechst ersteinmal Rekursion verstehen...
	myData->iSubLevel--;
	return TRUE;
}

BOOL CALLBACK MyEnumWindowsProc(HWND hWndParent, LPARAM lParam)
{
	sMyData* myData=(sMyData*)lParam;
	if(myData->bPhotoButtonFound) return TRUE;
	char* sBuffer = new char[GetWindowTextLength(hWndParent)];
	int n=GetWindowText(hWndParent, sBuffer, 1024);
	bool b=(strcmp(sBuffer, myData->sParent)==0);
	bool b1=(strcmp(sBuffer, myData->sChild)==0);
	delete [] sBuffer;
	if(myData->bInSubOfTSView && b1)
	{
		myData->bPhotoButtonFound=true;
		myData->hWndPhoto=hWndParent;
		return TRUE;// stop recursion here (find first match)
	}
	if(b) myData->bInSubOfTSView=true;
	EnumChildWindows(hWndParent, &MyEnumChildProc, lParam);
	if(b) myData->bInSubOfTSView=false;
	return TRUE;
}

HWND bGetMeWinHandle(char* sParent, char* sChild)
{
	sMyData myData={sParent, sChild, 0, false, false, NULL};
	if(!EnumWindows(&MyEnumWindowsProc, (LPARAM)(&myData)))
	{
		MessageBox(NULL, "!EnumWindows", "Fehler", MB_OK|MB_ICONERROR);
		return false; // GetLastError();
	}
	// myData.bPhotoButtonFound
	return myData.hWndPhoto;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int)
{
	HWND hWndPhoto=bGetMeWinHandle("TSView", "Photo");
	if(hWndPhoto==NULL)
	{
		MessageBox(NULL, "Photo Button leider nicht gefunden. :-(", "Sorry.", MB_OK|MB_ICONINFORMATION);
		return GetLastError();
	}
	
	LPARAM p=(2 << 16)+2; // position x=2 und y=2
	SendMessage(myData.hWndPhoto, WM_LBUTTONDOWN, NULL, p);
	Sleep(100);//ms
	SendMessage(myData.hWndPhoto, WM_LBUTTONUP, NULL, p);
	
	Sleep(5000);//ms
	bGetMeWinHandle("TSView oder hauptfenstername", "name vom OK button");
	
	return 0;
}
