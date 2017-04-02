#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import subprocess
import json
import common

test_dir = "../Test/parser/"
program = "./parser"

def generate_error_output(error_list):
    """
    Given an error_list.
    Translate it into an error output.
    """
    result = ""
    for error in error_list:
        result += "Error type %s at Line %d: .\n" % (error[1], error[0])
    return result

def check_error_output(output, error_list):
    lines = output.split("\n")
    length = len(error_list)
    # check whether the number of lines does not match
    # here we use length + 1
    # since there are n lines in the output
    # so there are n "\n"
    # split the output with "\n" and we will get n + 1 strings
    # the last one is an empty string
    if len(lines) != length + 1:
        return False
    for i in range(0, length):
        # extract line and error_type from parser's output
        words = lines[i].split()
        error_type = words[2]
        # be careful of the ":" following the line number
        error_line = int(words[5].split(":")[0])
        if error_type != error_list[i][1] or error_line != error_list[i][0]:
            return False
    return True

def run_test(cmm_file):

    testcase = cmm_file.split(".")[0]
    common.colored_print("%s:" % testcase, common.BLUE)
    output = subprocess.check_output("%s %s%s" % (program, test_dir, cmm_file), shell=True)

    # write the output of parser to a file
    with open(test_dir + testcase + ".out", "w") as f:
        f.write(output)

    # open the answer file
    with open(test_dir + testcase + ".answer", "r") as f:
        answer = f.read()

    # for wrong testcases
    # the corresponding answer file contains a json string
    # that describes on which line there is an error of which type(A or B)
    is_wrong_testcase = True
    try:
        error_list = json.loads(answer)
    except:
        is_wrong_testcase = False

    passed = False

    # check the output
    if is_wrong_testcase:
        correct = generate_error_output(error_list)
        passed = check_error_output(output, error_list)
    else:
        correct = answer
        if output == correct:
            passed = True

    if passed:
        common.colored_print("\tPass", common.GREEN)
    else:
        common.colored_print("\tFailed", common.RED)

    # put the correct answer in .correct file
    with open(test_dir + testcase + ".correct", "w") as f:
        f.write(correct)

if __name__ == "__main__":
    cmm_files = []
    argc = len(sys.argv)
    if argc >= 2:
        # user has specified which test to run
        for i in range(1, argc):
            cmm_file = sys.argv[i].split("-")[1] + ".cmm"
            cmm_files.append(cmm_file)
    else:
        # otherwise we run all the testcases
        output = subprocess.check_output("cd %s; ls *.cmm" % test_dir, shell=True)
        cmm_files = output.split()

    for cmm_file in cmm_files:
        run_test(cmm_file)
