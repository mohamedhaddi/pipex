# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pipex_leaks_tester.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/12 23:01:50 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/13 00:14:58 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os
import time

if not os.path.exists("./pipex"):
    print("Compile your project first, and name your program `pipex`.")
    exit()

"""
    - Only prints the outputs diff for tests with valid arguments.
    - Prints only errors for invalid arguments tests (doesn't print output files).
    - Doesn't check for memory leaks.
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
    "grep ' '",
]

leaks = "leaks --atExit --"
leaks_file = "tester_files/leaks"

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
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST I.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1


def test_invalid_num_args():
    print("\033[03;33m" + "TEST II ### INVALID NUM OF ARGS ###" + "\033[0m")
    print()
    count = 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}")'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out} oof)'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST II.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1


def test_invalid_files():
    print("\033[03;33m" + "TEST III ### INVALID FILES ###" + "\033[0m")
    print()
    count = 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inps = ["tester_files/", "tester_files/invalid"]
            for inp in inps:
                out = outfile1
                usr_test = (
                    f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out})'
                    + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
                )
                os.system(usr_test)
                time.sleep(0.5)
                print(
                    "\033[96m" + f"TEST III.{count}: " + "-" * 75 + "\033[0m",
                    usr_test,
                    sep="\n",
                )
                print()
                print(open(leaks_file, "r").read())
                count += 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out = "tester_files/"
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST III.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
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
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST IV.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1


def test_invalid_order():
    print("\033[03;33m" + "TEST V ### INVALID ORDER ###" + "\033[0m")
    print()
    count = 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex "{cmd1}" {inp} "{cmd2}" {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex "{cmd1}" "{cmd2}" {inp} {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1
    for cmd1 in cmds:
        for cmd2 in cmds:
            inp = infile
            out = outfile1
            usr_test = (
                f'({leaks} ./pipex {inp} "{cmd1}" "{cmd2}" {out})'
                + f' 2>/dev/null | grep "total leaked bytes" > {leaks_file}'
            )
            os.system(usr_test)
            time.sleep(0.5)
            print(
                "\033[96m" + f"TEST V.{count}: " + "-" * 75 + "\033[0m",
                usr_test,
                sep="\n",
            )
            print()
            print(open(leaks_file, "r").read())
            count += 1


test_valid_args()
test_invalid_num_args()
test_invalid_files()
test_invalid_cmds()
test_invalid_order()
