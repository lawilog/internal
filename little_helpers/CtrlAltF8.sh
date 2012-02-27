#!/bin/bash
xauth add :2 . `mcookie`
export __GL_FSAA_MODE=5
export LC_ALL="de_DE.utf8"
export LANG="de_DE.utf8"
xinit $1 -- :2 -xf86config xorg.conf.1screen
