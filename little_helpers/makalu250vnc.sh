#!/bin/bash
vncid=$(ssh lawi9838@makalu250.rz.tu-ilmenau.de "~/bin/vnc-id.sh")
~/downloads/software/realvnc-viewer-5.1.0-x64 -UserName=lawi9838 makalu250.rz.tu-ilmenau.de:$vncid &
