#!/bin/bash

BIN1=randomNum
BIN2=sizeof
BIN3=toBits
BIN4=toDec
#BINS=$BIN1 $BIN2 $BIN3 $BIN4
OLDPWD=$PWD
MYPATH=~/bin/

mkdir -p $MYPATH
make
mv $BIN1 $BIN2 $BIN3 $BIN4 $MYPATH/
#export PATH="$PATH:/home/arrigo/bin"
echo 'export PATH="$PATH:/home/arrigo/bin"' >> ~/.bashrc
source ~/.bashrc

#se gia esiste export in bashrc non mettere, mettere la condizione

