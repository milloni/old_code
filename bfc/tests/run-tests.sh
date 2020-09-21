#!/bin/bash

tests_cnt=0
passed_cnt=0
failed_cnt=0

# Runs bfci with a specified input file and checks if the output
# is the same as expected.
# Params:
#   $1: path to the bfci executable
#   $2: path to the brainfuck script
#   $3: expected result
#   $4: (optional) input to pass to the brainfuck script
# Return value:
#   true if the output is as expected, false if an error occurred or the
#   output differs from the expected.
function run_command {
    [[ -x "$1" ]] || return 1
    [[ -e "$2" ]] || return 1

    result=$(echo "$4" | "$1" "$2")
    if [[ "$result" = "$3" ]]; then
        return 0
    else
        return 1
    fi
}

# Wrapper for run_command. Performs the test and prints a message
# accordingly.
# Params:
#   $1: name of the test
#   $2: path to the bfci executable
#   $3: path to the brainfuck script
#   $4: expected result
#   $5: (optional) input to pass to the brainfuck script
function run_test {
    tests_cnt=$((tests_cnt+1))

    if run_command "$2" "$3" "$4" "$5"; then
        passed_cnt=$((passed_cnt+1))
        echo -e "[\e[32mPASS\e[0m] Test #${tests_cnt}: $1"
    else
        failed_cnt=$((failed_cnt+1))
        echo -e "[\e[31mFAIL\e[0m] Test #${tests_cnt}: $1"
    fi
}

# Prints the summary, including number of tests performed, number of tests
# passed, and number of tests failed.
function print_summary {
    echo "Summary:"
    echo "========"
    echo
    echo -e "Tests run:\t${tests_cnt}"
    echo -e "Tests passed:\t${passed_cnt}"
    echo -e "Tests failed:\t${failed_cnt}"
}

cd $(dirname "$0")
bfc_path=../bin/bfci
examples_path=../examples

run_test "hello_world" "$bfc_path" "$examples_path/hello.bf" "Hello World!"
run_test "rot13_abc"   "$bfc_path" "$examples_path/rot13.bf" "nop" "abc"
echo
print_summary

