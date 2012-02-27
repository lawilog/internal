#!/bin/bash
xauth add :2 . `mcookie`
export __GL_FSAA_MODE=5
xinit xmessage Hello -- :2
#VBoxManage startvm WinXP -- :2
# -xf86config xorg.conf.1screen
