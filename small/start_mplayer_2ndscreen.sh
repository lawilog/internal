#!/bin/bash
xauth add :2 . `mcookie`
export __GL_FSAA_MODE=5
xinit xterm -- :2 -xf86config xorg.conf.twinview
