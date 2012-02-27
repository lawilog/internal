#!/bin/bash
xauth add :2 . `mcookie`
export __GL_FSAA_MODE=5
xinit /usr/games/bin/ut2004 -- :2 -xf86config xorg.conf.1screen
