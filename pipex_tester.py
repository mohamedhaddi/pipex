# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_tester.py                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/12 23:01:40 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/20 14:00:37 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import filecmp
import difflib
import time

if not os.path.exists("./pipex"):
    print("Compile your project first, and name your program `pipex`.")
    exit()

"""
    You can go to the end of this file and comment out the function calls
    you don't want to test for now.
"""

"""
    # Only prints the diff of output files for tests with valid arguments.
    # Only prints errors for tests with invalid arguments (doesn't print
    their output files).
    # Prints diff for exit status (except, of course, for tests with invalid
    number of arguments).
    # Doesn't check for memory leaks.
    # Only tests the mandatory part for now.
"""

"""
    Change the content of your input file here:
"""

inp_content = "hi\ncv?\ntest space\n"

"""
    Add commands you want to test here:
"""

cmds = [
    "cat",
    "cAt",
    "bash",
    "chmod",
    "ls",
    "pwd",
    "grep ' '",
]

if not os.path.exists("tester_files"):
    os.makedirs("tester_files")

inp_file = open("tester_files/infile", "w+")

inp_file.write(inp_content)
inp_file.close()
infile = "tester_files/infile"
outfile1 = "tester_files/outfile1"
outfile2 = "tester_files/outfile2"


def test_valid_args():
    print("\033[03;33m" + "TEST I ### VALID ARGS ###" + "\033[0m")
    print()
    count = 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out1 = outfile1
            out2 = outfile2
            sys_test = (
                f"(< {inp} {cmd1} | {cmd2} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST I.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            if filecmp.cmp(out1, out2):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open(out1).readlines()
                text2 = open(out2).readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open(out1).readlines()
                text2 = open(out2).readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
                usr_errors_file = open("tester_files/errors2", "r")
                usr_errors = usr_errors_file.read()
                print(
                    "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1


def test_invalid_num_args():
    print("\033[03;33m" + "TEST II ### INVALID NUM OF ARGS ###" + "\033[0m")
    print()
    count = 1
    new_cmds = [
        "cat",
        "grep c",
    ]

    # zero arg
    usr_test = f'(./pipex) 2>tester_files/errors2'
    os.system(usr_test)
    time.sleep(0.5)
    usr_errors_file = open("tester_files/errors2", "r")
    usr_errors = usr_errors_file.read()
    print(
        "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
        usr_test,
        sep="\n",
    )
    print(
        "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
        usr_errors,
        sep="\n",
    )
    print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
    print()
    count += 1

    # one arg
    inp = infile
    usr_test = f'(./pipex {inp}) 2>tester_files/errors2'
    os.system(usr_test)
    time.sleep(0.5)
    usr_errors_file = open("tester_files/errors2", "r")
    usr_errors = usr_errors_file.read()
    print(
        "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
        usr_test,
        sep="\n",
    )
    print(
        "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
        usr_errors,
        sep="\n",
    )
    print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
    print()
    count += 1

    # two args
    inp = infile
    usr_test = f'(./pipex {inp} "{new_cmds[0]}") 2>tester_files/errors2'
    os.system(usr_test)
    time.sleep(0.5)
    usr_errors_file = open("tester_files/errors2", "r")
    usr_errors = usr_errors_file.read()
    print(
        "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
        usr_test,
        sep="\n",
    )
    print(
        "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
        usr_errors,
        sep="\n",
    )
    print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
    print()
    count += 1

    # three args
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}") 2>tester_files/errors2'
            os.system(usr_test)
            time.sleep(0.5)
            usr_errors_file = open("tester_files/errors2", "r")
            usr_errors = usr_errors_file.read()
            print(
                "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            count += 1

    # four args
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            out1 = outfile1
            usr_test = (
                f'(./pipex {inp} "{cmd1}" "{cmd2}" {out1} oof) 2>tester_files/errors2'
            )
            os.system(usr_test)
            time.sleep(0.5)
            usr_errors_file = open("tester_files/errors2", "r")
            usr_errors = usr_errors_file.read()
            print(
                "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            count += 1


def test_invalid_files():
    print("\033[03;33m" + "TEST III ### INVALID FILES ###" + "\033[0m")
    print()
    count = 1
    new_cmds = [
        "cat",
        "grep c",
    ]
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inps = ["tester_files/", "tester_files/invalid"]
            for inp in inps:
                out1 = outfile1
                out2 = outfile2
                sys_test = (
                    f"(< {inp} {cmd1} | {cmd2} > {out1};"
                    + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
                )
                usr_test = (
                    f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2};'
                    + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
                )
                os.system(sys_test)
                time.sleep(0.5)
                os.system(usr_test)
                time.sleep(0.5)
                sys_errors = open("tester_files/errors1", "r").read()
                usr_errors = open("tester_files/errors2", "r").read()
                print(
                    "\033[96m" + f"TEST III.{count}: " + "-" * 75 + "\033[0m",
                    sys_test,
                    usr_test,
                    sep="\n",
                )
                print()
                print(
                    "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
                print()
                print("\033[96m" + "exit_status diff: " + "\033[0m")
                print()
                if filecmp.cmp(
                    "tester_files/exit_status1", "tester_files/exit_status2"
                ):
                    print("\033[03;92m" + "Good" + "\033[0m")
                    print()
                    text1 = open("tester_files/exit_status1").readlines()
                    text2 = open("tester_files/exit_status2").readlines()
                    for line in text1:
                        print(line)
                    for line in text2:
                        print(line)
                else:
                    print("\033[03;91m" + "No good" + "\033[0m")
                    print()
                    text1 = open("tester_files/exit_status1").readlines()
                    text2 = open("tester_files/exit_status2").readlines()
                    for line in difflib.unified_diff(text1, text2):
                        print(line)
                    print()
                count += 1
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            out1 = "tester_files/"
            out2 = "tester_files/"
            sys_test = (
                f"(< {inp} {cmd1} | {cmd2} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("tester_files/errors1", "r").read()
            usr_errors = open("tester_files/errors2", "r").read()
            print(
                "\033[96m" + f"TEST III.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                sys_errors,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1


def test_invalid_cmds():
    print("\033[03;33m" + "TEST IV ### INVALID COMMANDS ###" + "\033[0m")
    print()
    count = 1
    inv_cmds = [
        "cat",  # for testing a valid one with an invalid one, and vice versa.
        "AS2Gxz -l",
        "CsX3Lm",
    ]
    for cmd1 in inv_cmds:
        for cmd2 in inv_cmds:
            inp = infile
            out1 = outfile1
            out2 = outfile2
            sys_test = (
                f"(< {inp} {cmd1} | {cmd2} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("tester_files/errors1", "r").read()
            usr_errors = open("tester_files/errors2", "r").read()
            print(
                "\033[96m" + f"TEST IV.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                sys_errors,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1


def test_invalid_order():
    print("\033[03;33m" + "TEST V ### INVALID ORDER ###" + "\033[0m")
    print()
    count = 1
    new_cmds = [
        "cat",
        "grep c",
    ]
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            out1 = outfile1
            out2 = outfile2
            sys_test = (
                f"(< {cmd1} {inp} | {cmd2} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex "{cmd1}" {inp} "{cmd2}" {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("tester_files/errors1", "r").read()
            usr_errors = open("tester_files/errors2", "r").read()
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                sys_errors,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            out1 = outfile1
            out2 = outfile2
            sys_test = (
                f"(< {cmd1} {cmd2} | {inp} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex "{cmd1}" "{cmd2}" {inp} {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("tester_files/errors1", "r").read()
            usr_errors = open("tester_files/errors2", "r").read()
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                sys_errors,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1
    for cmd1 in new_cmds:
        for cmd2 in new_cmds:
            inp = infile
            out1 = outfile1
            out2 = outfile2
            sys_test = (
                f"(< {inp} {cmd1} | {cmd2} > {out1};"
                + " echo $? > tester_files/exit_status1) 2>tester_files/errors1"
            )
            usr_test = (
                f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2};'
                + " echo $? > tester_files/exit_status2) 2>tester_files/errors2"
            )
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("tester_files/errors1", "r").read()
            usr_errors = open("tester_files/errors2", "r").read()
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                sys_test,
                usr_test,
                sep="\n",
            )
            print()
            print(
                "\033[96m" + "SYSTEM'S ERROR MSGS:" + "\033[0m",
                sys_errors,
                sep="\n",
            )
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
            print("\033[03;92m" + "All good? Errors handled and all?" + "\033[0m")
            print()
            print("\033[96m" + "exit_status diff: " + "\033[0m")
            print()
            if filecmp.cmp("tester_files/exit_status1", "tester_files/exit_status2"):
                print("\033[03;92m" + "Good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in text1:
                    print(line)
                for line in text2:
                    print(line)
            else:
                print("\033[03;91m" + "No good" + "\033[0m")
                print()
                text1 = open("tester_files/exit_status1").readlines()
                text2 = open("tester_files/exit_status2").readlines()
                for line in difflib.unified_diff(text1, text2):
                    print(line)
                print()
            count += 1


test_valid_args()
test_invalid_num_args()
test_invalid_files()
test_invalid_cmds()
test_invalid_order()
