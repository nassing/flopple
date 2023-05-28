#!/bin/sh

/usr/bin/git fetch origin
/usr/bin/git reset --hard origin/master
echo ilovefloppa | /usr/bin/sudo -S service flopple restart