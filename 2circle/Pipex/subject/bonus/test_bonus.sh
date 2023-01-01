#!/bin/bash

rm file_b
rm file_bb

rm pipex
cc pipex_bonus.c -o pipex

# infile="file_a"
# cmd1="head -5"
# cmd2="ccat"
# cmd3="wc -l"
# outfile="file_b"

# < $infile $cmd1 | $cmd2 | $cmd3> $outfile

# outfile="file_bb"
# ./pipex $infile "$cmd1" "$cmd2" "$cmd3" $outfile

#cmd1의 에러 메시지가 출력되는 경우는 cmw2가 실패했을 경우임
#이경우를 사용할 수 있는 방법을 강9해보자

LIMIT="LIMIT"
cmd1="cat"
cmd2="wc"
outfile="file_b"

#$cmd1 <<< $LIMIT | $cmd2

outfile="file_bb"
./pipex "here_doc" $LIMIT "$cmd1" "$cmd2" $outfile