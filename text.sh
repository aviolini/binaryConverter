#!/bin/bash


ls
pwd
echo test test "test" 'test   t'  test
echo -n test test "test" 'test   t'  test
cd ..
pwd
cd $OLDPWD
pwd
cd ../../
pwd
cd $OLDPWD
pwd

export Z=1
export
export Z+=1
export
export ZZ
export ZZZ=
export
unset Z
export
export Z=2
echo $?
export
echo $?

#errori
export =3
export =4=5
echo $?
export Z =6
export Z = 7
export Z= 8
echo $?
export ZD= '12      13'
echo $?

#ok
export "ZA"=9
export ZB="10"
export ZC='11'
export ZD=14 ZE= ZF "ZG" 'ZH'
export

unset Z
unset ZA
unset ZB
unset ZC
unset ZD
unset ZE
unset ZF
unset ZG
unset ZH
unset ZZ
unset ZZZ
export

echo $?


#outfile
echo 1 >infile
cat infile
echo 2 >"infile"
cat infile
echo 3 >'infile'
cat infile
echo 4 > "infile"
cat infile
echo 5 > 'infile'
cat infile
echo 6 >     "infile"
cat infile
echo 7 >"infile         ."
cat "infile         ."
echo 8a>infile
cat infile
echo 9a>     "infile        ."
cat      "infile        ."
echo 10a>'infil   e            '
cat '.         infile'
echo 11 >"infile""outfile"
cat "infile""outfile"
echo 12 > "infi"le'out'fil"e2"
cat "infi"le'out'fil"e2"
echo 13 > infi'l e o'u't'"file3"
cat infi'l e o'u't'"file3"
echo 14 > infile""''
cat infile""''
echo 15 >infi'leo'>infileou>infileout>infileoutf>      infileoutfi>"infile"outfil
ls

#infile
cat<infile
cat<"infile"
cat<'infile'
cat< "infile"
cat< 'infile'
cat<     "infile"
cat<"infile         ."
cat<     "infile        ."
cat<'.         infile'
cat <"infile""outfile"
cat < "infi"le'out'fil"e2"
cat < infi'l e o'u't'"file3"
cat < infile""''

# cat >>infil
# cat infil

echo 12 >infile
echo 123 >>infile
echo 1234 >>infile
echo 12345 >>infile
echo 123456 >> infile
echo 1234567 >> infile
echo 12345678 >> infile
echo 123456789 >> infile
echo 1234567 >outfile
echo 12345678 > infil

<infile<outfile>outfile<infil<infile cat -e
cat outfile

<infile cat >outfil<infileo -t <infil<infile -e >outfile -n
cat outfile

cat <infile >outfil    <infileo -t <infil<infile -e       >outfile
cat outfile

cat <infile >outfil<infileo -t<infil<infile -e>>outfile -n
cat outfile


echo 2 | echo 3 | echo 4 | echo 5 | echo 6 | echo 7 | echo 8 | echo 9


<infile cat -e | grep 2
<infile cat -e | grep 2 | grep 3
<infile cat -e | grep 2 | grep 3 | grep 4
<infile cat -e | grep 2 | grep 3 | grep 4 | grep 5
<infile cat -e | grep 2 | grep 3 | grep 4 | grep 5 | grep 6 | grep 7 | grep 8 | grep 9
#ok premere CTRL-D piu' volte
# cat -e | grep 2 | grep 3 | <infile >outfile grep 4 | grep 5 | grep 6 | grep 7 | grep 8 | grep 9
# cat outfile
# cat -e | grep 2 | grep 3 <infile grep 4 | grep 5 | grep 6 > outfile | grep 7 | grep 8 | grep 9
# cat outfile
# cat -e | grep 2 | grep 3 >outfile grep 4 | grep 5 | grep 6 <infile | grep 7 | grep 8 | grep 9
# cat outfile

cat -e  <infile | cat -t >outfile | grep 3 | grep 4 | grep 5 | grep 6 | grep 7 | grep 8 | cat -e | cat -t | cat -n
cat outfile

<infile cat -e | grep 2 | grep 3 | grep 4 | grep 5 | grep 6 | grep 7 | grep 8 | cat -e | cat -t | cat -n >outfile
cat outfile


#variabili:
echo $Z
echo "$Z"
echo "$LANG"
echo $ZZ
echo '$TERM'
echo $TERM
echo $TERM    '   "$TERM test '   "$TERM"  test  te$TERM\s\t
echo $TERM    '   "$TERM test '   "$TERM"  test  te$TERM\s\t > outfile
echo $TERM "$LANG" test'$LANG"" 'test " test$LANG test''test" test""
echo '' TERM $TERM "$LANG" "$LANG'" "$LANG'" "'$LANG'" '"$LANG"'"$LANG"'$LANG'$LANG
echo "$TERM$LANG$PWD"$PWD'$PWD'
echo ""$TERM$LANG$PWD"$PWD'$PWD'"
echo ""$TERM$LANG$PWD"$PWD'$PWD'"   >outfile
echo "'$TERM"' '"$TERM'" '$TERM'" $TER"
echo '$TERM'"$PWD$L"$L"$LAN $     PATH" $  PATH "$"PATH '$'PATH
echo ''$TERM'"$PWD$L"$L"$LAN $     PATH" $  PATH "$"PATH '$'PATH'
echo " $TERM '$PATH' $ LANG $LANG '$'LANG "
echo ' $TERM "$PATH" $ LANG $LANG "$"LANG '

#exit:
#exit
#CTRL+D

#variabile errori:
#ls
#echo $?
#lx
#echo $?

#unset effettivo variabili:
#echo $PATH
#unset PATH
#echo $PATH
#ls

#heredoc:
#<<stop 
#<<stop cat
#<<stop cat >outfile 

#signal:
#CTRL + \
#CTRL + D
#CTRL + C
#nel programma principale minishell:
#dopo aver avviato cat senza argomenti o grep a
#con <<infile con o senza cat

#error:
# >
# <
# >>
# <<
# >>>
# <<<
# <>
# ><
# >><
# <inf
# <infile >
# >outfile >
# <infile ><
# >outfile <>