rm -f push_swap
cc main.c greedy_algo.c greedy_counter.c operation1.c operation2.c operation3.c primary_logic.c stack_operation.c print_function.c util.c util2.c -o push_swap 
# ARGS="$(seq 100 | sort -R | xargs)"
# echo $ARGS
# ./push_swap $ARGS 
# ./push_swap $ARGS | ./checker_Mac $ARGS 



#./checker_Mac "1 2" 3 "  4 5" "7"
#./checker_Mac "1 2"



#ARGS="-2147483648 -2147483646 -2147483645 -2147483644 -2147483643 -2147483642 2147483647"
# ./push_swap 1 2 3 4 -
# ./push_swap "-"
# ./push_swap "-one"
# ./push_swap " 1 one  2 3  4 "
# ./push_swap 1 "  2 3  4 " 1
# ./push_swap 2 +3  4- " "
# ./push_swap 2147483648 +3  4- " "
# ./push_swap +2147483648 +3  4- " "
# ./push_swap +2147483648 "++3"  4- " "
# ./push_swap "++3" 4- " "
# ./push_swap -2147483649 " "
# ./push_swap " "
# ./push_swap "" 33

max=0
min=1000000
for var in {1..100}
do
	ARGS="$(seq 100 | sort -R | xargs)"

	# ./push_swap $ARGS | ./checker_Mac $ARGS
	# ./push_swap $ARGS | wc -l | tr -d ' '
	str=$(./push_swap $ARGS | ./checker_Mac $ARGS)
	tmp=$(./push_swap $ARGS | wc -l | tr -d ' ')

	if [ $str == "KO" ]
	then
		echo $ARGS
	else
		echo $str
		./push_swap $ARGS | wc -l | tr -d ' '
	fi

	if [ $((tmp)) -gt $((max)) ]
	then
		max=$tmp
	fi
done
echo $max

#rm -f push_swap
# FAILARGS="8  11  4  24  14  30  29  12  27  1  5 16 25 20 28 17 3 21 2 7 26 10 19 15 13 6 9 23 18 22"
# # FAILARGS="1 7 9 2 11 19 13 20 17 18 10 5 16 8 14 12 3 4 6 15"
# # FAILARGS="9 2 6 4 10 7 3 12 1 11 5 8 13"
# ./a.out $FAILARGS
# ./a.out $FAILARGS | ./checker_Mac $FAILARGS 