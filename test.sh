make clean

# compile and check if compilation was successful
make
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# unzip if not already unzipped
if [ ! -d "hw1-tests" ]; then
    unzip hw1-tests.zip
fi

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

shopt -s nullglob
declare -i FAILED_TESTS=0
declare -i OUTPUT_FAILED=0
declare -i TOTAL_TESTS=0
FAILED_LIST=""

diff_flags="-u"

for i in {1..28} ; do
    TOTAL_TESTS+=1
  
    test_file="hw1-tests/t$i.in"
    output_file="hw1-tests/output$i.txt"
    expected_output="hw1-tests/t$i.in.out"
    printf 'test %d: %s >>>   ' "$i" "$test_file"
    
    ./hw1 < $test_file > $output_file
    	
    diff $diff_flags $output_file $expected_output > diff$i.txt
    
    	if [ $? -eq 0 ]
    	then
    	  		  printf "${GREEN}pass${NC}\n"
    	else
    		printf "${RED}fail${NC}\n"
    		FAILED_TESTS+=1
    		OUTPUT_FAILED+=1
    		FAILED_LIST+="$i\n"
    		cat diff$i.txt
    		printf "\n"
    	fi
    	rm "diff$i.txt"
done

printf "\n\nTotal tests ran: ${TOTAL_TESTS}\n"

if [ ${FAILED_TESTS} -eq 0 ]; then
	printf "\n${GREEN} All tests passed :)${NC}\n\n"
else
	printf "\n${RED} Failed ${FAILED_TESTS}${NC} tests.\n${FAILED_LIST}\n\n"
	printf "Output fail: ${OUTPUT_FAILED}\n"
	printf "Valgrind fail: ${VALGRIND_FAILED}\n"
fi

#for i in {1..28} ; do
#    if [ -s "diff$i.txt" ]; then
#        printf '\n\nTest %d failed\n' "$i"
#        cat "diff$i.txt"
#    fi
#    rm -r  "diff$i.txt"
#done



#!/bin/bash


#
#help_message="\ntester.sh: tester.sh [tests] [-v] [-p] [--style=[diff options]] \n\n\t tests\t\t\t\t -a to run all tests or \n\t\t\t\t\t --tests=[NUM]\t NUM is number that specifies number of tests to run, defaults to $TESTS_TO_RUN\n\t -v\t\t\t\t run valgrind\n\t -p\t\t\t\t print every test result individually\n\t --style=[diff options]\t\t add flags to diff\n\t\t diff options\t\t flags added to diff command\n"
#compilation_failed_message="\nCompilation Failed.\nTesting Terminated\n\n"



#for i in fileTests/inFiles/test*.in
#do
#
#
#  T
#done



printf "Use rm hw1-tests/output* to remove all output files\n\n"

