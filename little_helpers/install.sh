#!/bin/bash
echo sda1 30GB NTFS Windows
echo sda2 10GB HFS MacOS X
echo sda3 20GB ReseiferFS Gentoo
echo sda4 Rest extended
echo sda5   2 GB swap swap
echo sda6   Rest ext2 /home
fdisk /dev/sda
fdisk -h -l /dev/sda
echo create fs;read enter
mkreiserfs /dev/sda3
mkswap /dev/sda5
mke2fs /dev/sda6
mount /dev/sda3 /mnt/gentoo
mkdir /mnt/gentoo/boot
mount | grep gentoo
ls -l /mnt/gentoo
date
echo unpack stage3;read enter
tar xvjpf stage3-*.tar.bz2 -C /mnt/gentoo/
ls -l /mnt/gentoo
echo OK? than manually copy portage tree now to /mnt/gentoo/usr/portage;read enter

echo Patching etc/make.conf
echo CFLAGS=\"-march=k8 -O2 -pipe -fomit-frame-pointer\" >> /mnt/gentoo/etc/make.conf
echo MAKEOPTS=\"-j2\" >> /mnt/gentoo/etc/make.conf >> /mnt/gentoo/etc/make.conf
echo MEDIA_SUPPORT=\"a52 aac alsa ao arts audiofile bzip2 dv dvd ffmpeg flac gif jpeg jpeg2k lame latex lirc mime mp3 mpeg musepack nas matroska ogg openal pdf pulseaudio quicktime raw sndfile sox speex svg scga szip tetex tiff theora v4l v4l2 vcd vorbis wavpack win32codecs x264 xine xosd xpm xvid zlib\" >> /mnt/gentoo/etc/make.conf
echo CHAT_SUPPORT=\"-aim history icq irc -jabber -msn -yahoo\" >> /mnt/gentoo/etc/make.conf
echo USE=\"\$MEDIA_SUPPORT \$CHAT_SUPPORT X acpi apm bash-completion bidi bluetooth branding cdinstall cdparanoia cdr cracklib crypt css cups dga dri dvdr dvdread -emacs encode ftp gimp -gnome gnuplot -gtk hal ieee1394 imap ipv6 java javascript kde libnotify libwww -multilib nls nntp nocd -odbc opengl -oracel pcmcia qt3 qt4 readline rss samba smartcard sse sse2 ssl startup-notification spell usb wifi xinerama xinetd xml xsl\" >> /mnt/gentoo/etc/make.conf
echo FEATURES=\"ccache\" >> /mnt/gentoo/etc/make.conf
echo CCACHE_DIR=\"/var/tmp/ccache/\" >> /mnt/gentoo/etc/make.conf
echo CCACHE_SIZE=\"2G\" >> /mnt/gentoo/etc/make.conf
echo LIRC_DEVICES=\"devinput\" >> /mnt/gentoo/etc/make.conf
echo VIDEO_CARDS=\"nv\" >> /mnt/gentoo/etc/make.conf
echo LINGUAS=\"de\" >> /mnt/gentoo/etc/make.conf
nano -w /mnt/gentoo/etc/make.conf

echo Patching etc/resolv.conf
cat /mnt/gentoo/etc/resolv.conf
echo search fem.tu-ilmenau.de > /mnt/gentoo/etc/resolv.conf
echo nameserver 141.24.53.248 >> /mnt/gentoo/etc/resolv.conf
echo nameserver 141.24.53.227 >> /mnt/gentoo/etc/resolv.conf
nano /mnt/gentoo/etc/resolv.conf

echo Patching etc/locale.gen
cat /mnt/gentoo/etc/locale.gen
echo en_US ISO-8859-1 > /mnt/gentoo/etc/locale.gen
echo en_US.UTF-8 UTF-8 >> /mnt/gentoo/etc/locale.gen
echo de_DE ISO-8859-1 >> /mnt/gentoo/etc/locale.gen
echo de_DE@euro ISO-8859-15 >> /mnt/gentoo/etc/locale.gen
nano /mnt/gentoo/etc/locale.gen

cp -v /mnt/gentoo/usr/share/zoneinfo/Europe/Berlin /mnt/gentoo/etc/localtime

echo HOSTNAME=\"deepnote\" >> /mnt/gentoo/etc/conf.d/hostname
nano /mnt/gentoo/etc/conf.d/hostname

nano /etc/issue

echo Patching etc/conf.d/net
echo "config_eth1=( \"dhcp\" )" >> /mnt/gentoo/etc/conf.d/net
echo "dhcpd_eth1=\"-t 20\"" >> /mnt/gentoo/etc/conf.d/net
nano /mnt/gentoo/etc/conf.d/net

nano -w /mnt/gentoo/etc/rc.conf
nano -w /mnt/gentoo/etc/conf.d/keymaps
nano -w /mnt/gentoo/etc/conf.d/clock

echo sda3 ReseiferFS Gentoo
echo sda5 swap swap
echo sda6 ext2 /home
echo edit /mnt/gentoo/etc/fstab;read enter
nano -w /mnt/gentoo/etc/fstab

echo chrooting...
mount -t proc none /mnt/gentoo/proc
mount -o bind /dev /mnt/gentoo/dev
cp -v ./install2.sh /mnt/gentoo/
chroot /mnt/gentoo /bin/bash