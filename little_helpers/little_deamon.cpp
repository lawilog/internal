#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		cout<<"usage: "<<argv[0]<<" port"<<endl;
		return 0;
	}
	int iPort=atoi(argv[1]);
	cout<<"will listen on port "<<iPort<<endl;
	
	int iServerSock = socket(AF_INET, SOCK_STREAM, 0);
	if(iServerSock<0) {cerr<<"Error: Could not create socket."<<endl; return -1;}
	sockaddr_in ServerData;
	bzero(&ServerData, sizeof(ServerData));
	ServerData.sin_family = AF_INET;
	ServerData.sin_addr.s_addr = INADDR_ANY;
	ServerData.sin_port = htons(iPort);
	if(bind(iServerSock, (const sockaddr*)&ServerData, sizeof(ServerData)) < 0) {cerr<<"Error: Could not bind."<<endl; return -1;}
	listen(iServerSock, 3);
	
	while(true)
	{
		sockaddr_in ClientData;
		int iClientLen=sizeof(ClientData);
		int iClientSock=accept(iServerSock, (sockaddr*)&ClientData, (socklen_t*)&iClientLen);
		if(iClientLen<0) {cerr<<"Error: Could not accept."<<endl; return -1;}
		char sBuffer[256];
		bzero(sBuffer, 256);
		int n=read(iClientSock, sBuffer, 255);
		if(n<0) {cerr<<"Error: Could not read."<<endl; return -1;}
		cout<<"Received the message: "<<sBuffer<<endl;
		n=write(iClientSock, "Understood. I will restart the internet connection now.\n", 56);
		system("/etc/init.d/net.ppp0 restart &");
		if(n<0) {cerr<<"Error: Could not write."<<endl; return -1;}
		close(iClientSock);
	}
	return 0;
}
