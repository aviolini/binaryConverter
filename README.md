**Do it in the console is better than do it in the browser!**

*DoItInConsole is a collection of useful applications that you can run from the console rather than using the internet browser*

### APPLICATIONS DESCRIPTION:  
- randomNum.c:  
  *return n differrent and random numbers*

- sizeof.c:  
  *print sizes and limits of c variables*

- toBits.c:  
  *convert decimal number to binary*

- toDec.c:  
  *convert binary number to decimal*

### SIMPLE USE:  
- $make -> make programs in local directory  
  ./doit_randomNum 100  
  ./doit_sizeof  
  ./doit_toBits -128 -64 -32 -16 -8 -4 -2 -1 0 1 2 3 4 5 10 100 1000  
  ./doit_toDec 1 11 111 1111 11111 111111 100000

### INSTALL IN YOUR PC:  
__*only for Linux - only for bash*__  
*add application binaries in ~/bin/ and add ~/bin/ path to ~/.bashrc  
application binaries will be accessible everywhere*  
- $make install && source ~/.bashrc

### HELP:  
  ./doit_toBits help  
  ./doit_toDec help

### TEST:  
  ./doit_toBits test  
  ./doit_toDec test  

### UNINSTALL:  
 *remove application binaries from your pc*  
 - uninstall-utils.sh

 *or from repository dir:*  
 - $make uninstall
