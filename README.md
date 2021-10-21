# utils :

# APPLICATIONS DESCRIPTION:

- randomNum.c:

  return n differrent and random numbers

- sizeof.c:

  print sizes and limits of c variables

- toBits.c:

  convert decimal number to binary

- toDec.c:

  convert binary number to decimal

# SIMPLE USE:

- $make -> make programs in local directory

  ./randomNum 100
  
  ./sizeof
  
  ./toBits -128 -64 -32 -16 -8 -4 -2 -1 0 1 2 3 4 5 10 100 1000
  
  ./toDec 1 11 111 1111 11111 111111 100000
  
# INSTALL IN YOUR PC
(applications will be accessible everywhere - only for bash)

- $make install && source ~/.bashrc  -> install programs in ~/bin and add ~/bin path to ~/.bashrc

# HELP:

  ./toBits help
  
  ./toDec help
  
# TEST:

  ./toBits test
  
  ./toDec test
