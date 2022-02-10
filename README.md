# binaryConverter
A CLI application to convert from decimal to binary number and reverse

### DOWNLOAD
```shell
git clone git@github.com:aviolini/binaryConverter.git
```
```shell
cd ./binaryConverter
```
### INSTALL
**help installation**
```shell
make help
```
**locally (the apps can be called only from the project folder)**
```shell
make all
```
**system (the apps can be called everywhere - only for GNU/Linux system with bash)**
```shell
make install
```
```shell
source ~/.bashrc
```

### USAGE
**locally**
```shell
./converterToBits -128 -64 -32 -16 -8 -4 -2 -1 0 1 2 3 4 5 10 100 1000
```
```shell
./converterToDec 1 11 111 1111 11111 111111 100000
```
**system**
```shell
converterToBits -128 -64 -32 -16 -8 -4 -2 -1 0 1 2 3 4 5 10 100 1000
```
```shell
converterToDec 1 11 111 1111 11111 111111 100000
```
### UNINSTALL

**locally**
 ```shell
 make clean
```
 **system**
```shell
 uninstall-binaryConverter.sh
```
