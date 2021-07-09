#!/bin/bash


# if [ $1 = 0 ]
# then
# 	make 
# 	make clean
# fi
clear 
rm -rf out1
rm -rf out2
touch out1
touch out2

rm -rf out_err1
rm -rf out_err2
touch out_err1
touch out_err2



rm -f infil*
rm -f outfil*
bash text.sh >out1 2>out_err1




rm -f infil*
rm -f outfil*
./minishell text.sh >out2 2>out_err2




echo start_diff
diff out1 out2
echo end_diff

echo start_diff_err
diff out_err1 out_err2
echo end_diff_err

#QUOTES
#UNSET VAR PATH POI LS 