#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a extra=(
    "for test_grep.txt"
    "for test_grep.txt -o"
    "for test_grep.txt -on"
    "for test_grep.txt -oh"
    "for test_grep.txt -os"
    "for test_grep.txt -oi"
    "-f test_grep1.txt test_grep.txt"
    "-f test_grep1.txt test_grep.txt -h"
    "-f test_grep1.txt test_grep.txt -i"
    "-f test_grep1.txt test_grep.txt -v"
    "-f test_grep1.txt test_grep.txt -hns"
    "-f test_grep1.txt test_grep.txt -in"
    "-f test_grep1.txt test_grep.txt -inh"
    "-f test_grep1.txt test_grep.txt -inhs"
    "-f test_grep1.txt test_grep.txt -ov"
#"-f test_grep1.txt test_grep.txt -ivclnhs"
    "-f test_grep1.txt test_grep.txt -vi"
    "-f test_grep1.txt test_grep.txt -nivh"
    "-f test_grep1.txt test_grep.txt -ne"
)


testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    RESULT="SUCCESS"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
    else
      (( FAIL++ ))
        RESULT="FAIL"
    fi
    echo "[${SUCCESS}/${FAIL}] ${RESULT} grep $t"
    rm test_s21_grep.log test_sys_grep.log
}

# специфические тесты
for i in "${extra[@]}"
do
    var="-"
    testing $i
done

echo "SUCCESS: $SUCCESS"
echo "FAIL: $FAIL"
