#!/bin/bash

# rm file_b
# rm file_bb
#cc src/pipex.c src/pipex_make_command_path.c src/pipex_util.c src/libft/libft.a -o pipex

infile="file_a"
cmd1="cat"
cmd2=" cat"
outfile="file_b"

< $infile $cmd1 | $cmd2 > $outfile

outfile="file_bb"
./pipex $infile "$cmd1" "$cmd2" $outfile

# #cmd1의 에러 메시지가 출력되는 경우는 cmw2가 실패했을 경우임 ?? 이경우에도 출력둘다 됨(배쉬) 다시 확인하자
# #이경우를 사용할 수 있는 방법을 강9해보자

# LIMIT="LIMIT"
# cmd1="grep a"
# cmd2="cat"
# outfile="file_b"

# #$cmd1 <<< $LIMIT | $cmd2

# outfile="file_bb"
# ./pipex "here_doc" $LIMIT "$cmd1" "$cmd2" $outfile