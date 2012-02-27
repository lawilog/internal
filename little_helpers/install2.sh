#!/bin/bash
env-update
source /etc/profile
export PS1="(chroot) $PS1"

ls -FGg /etc/make.profile
echo "to change: ln -snf /usr/portage/profiles/<profile name> /etc/make.profile"
echo Enter;read enter

emerge gentoo-sources
cd /usr/src/linux
cp -v /.config ./
make && make modules_install
cp arch/x86_64/boot/bzImage /boot/kernel-2.6.24-r3
ln -s /boot/kernel-2.6.24-r3 /boot/kernel
echo /boot/;ls -l /boot/
echo /etc/init.d/net*;ls -l /etc/init.d/net*
echo set passwd;read enter

passwd

emerge -av app-admin/sudo app-admin/syslog-ng app-arch/gzip app-arch/unrar app-arch/zip app-cdr/k3b app-dicts/aspell-de app-doc/kchmviewer app-editors/kile app-editors/nano app-emulation/virtualbox app-emulation/wine app-misc/lirc app-office/openoffice app-portage/gentoolkit app-text/dvibook app-text/pdftk app-text/tetex dev-lang/php dev-util/ccache dev-util/subversion games-emulation/dosbox games-puzzle/einstein games-puzzle/enigma kde-base/ark kde-base/kdebase-meta kde-base/kdelirc kde-base/kmail kde-base/kmix kde-base/knewsticker kde-base/knode kde-base/kompare kde-base/kopete kde-base/kpdf kde-base/ksirtet kde-base/ksnapshot kde-base/ksvg kde-base/kuser kde-base/kview kde-misc/kdirstat media-fonts/corefonts media-fonts/font-misc-misc media-fonts/font-schumacher-misc media-fonts/freefonts media-fonts/x11fonts-jmk media-gfx/gimp media-libs/libquicktime media-sound/alsa-utils media-sound/amarok media-sound/audacity media-sound/lame media-sound/ogg2mp3 media-sound/vorbis-tools media-sound/wavplay media-tv/kdetv media-video/transcode media-video/vlc net-analyzer/macchanger net-analyzer/nmap net-fs/nfs-utils net-fs/samba net-ftp/ftp net-ftp/vsftpd net-im/skype net-misc/dhcp net-misc/dhcpcd net-misc/netkit-telnetd net-misc/ntp net-misc/openssh net-nntp/knews net-www/netscape-flash sci-mathematics/octave sci-mathematics/yacas sys-apps/hal sys-apps/less sys-apps/pciutils sys-apps/pcmciautils sys-apps/slocate sys-boot/grub sys-boot/syslinux sys-devel/gcc sys-fs/device-mapper sys-fs/dosfstools sys-fs/ntfsprogs sys-fs/reiserfsprogs sys-fs/squashfs-tools sys-fs/udev sys-kernel/gentoo-sources sys-process/vixie-cron sys-process/lsof www-client/links www-client/mozilla-firefox x11-apps/xev x11-apps/xsm x11-base/xorg-x11 x11-drivers/nvidia-drivers x11-libs/qt

rc-update add net.eth0 default
rc-update add syslog-ng default

echo edit grub.conf;read enter
nano -w /boot/grub/grub.conf
grub

rm /.config
rm /install2.sh