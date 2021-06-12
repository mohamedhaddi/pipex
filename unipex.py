import os
import subprocess
import filecmp
import difflib
import time

"""
    - Doesn't check memory leaks.
    - Doesn't print errors for valid arguments tests.
    - Will only print the tested inputs when they fail.

    - Can't use `assertEqual()` for errors since user error messages might be (in most
    cases) different than system error messages.

    If you don't want to compare errors comment out these two lines:
    # print("\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m", sys_errors, sep="\n")
    # print("\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m", usr_errors, sep="\n")
"""

if not os.path.exists("unipex_files"):
    os.makedirs("unipex_files")

inp_file = open("unipex_files/infile", "w+")

"""
    Change your input file here:
"""

inp_file.write("hi\ncv?\ntest space\ntest/slash\ntest\\backslash\n")

inp_file.close()

infile = "unipex_files/infile"
outfile1 = "unipex_files/outfile1"
outfile2 = "unipex_files/outfile2"

"""
    Add commands you want to test here:
"""

cmds = [
    "cat",
    "grep ' '",
]


print("\033[03;33m" + "### TESTING VALID ARGS" + "\033[0m")
print()
count = 1
for cmd1 in cmds:
    for cmd2 in cmds:
        inp = infile
        out1 = outfile1
        out2 = outfile2
        sys_test = f"(< {inp} {cmd1} | {cmd2} > {out1}) 2>errors"
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2}) 2>errors'
        os.system(sys_test)
        time.sleep(0.5)
        os.system(usr_test)
        time.sleep(0.5)
        # subprocess.check_call(sys_test, shell=True)
        # subprocess.check_call(usr_test, shell=True)
        test_msg = (
            "\033[03;34m"
            + f"TEST {count}:"
            + "\n"
            + "\n"
            + "System test: "
            + sys_test
            + "\n"
            + "./pipex test: "
            + usr_test
            + "\n"
            + "\033[0m"
        )
        if filecmp.cmp(out1, out2):
            print(test_msg)
            print("\033[03;92m" + "Good" + "\033[0m")
            print()
            text1 = open(out1).readlines()
            text2 = open(out2).readlines()
            for line in text1:
                print(line)
            for line in text2:
                print(line)
        else:
            print(test_msg)
            print("\033[03;91m" + "No good" + "\033[0m")
            print()
            text1 = open(out1).readlines()
            text2 = open(out2).readlines()
            for line in difflib.unified_diff(text1, text2):
                print(line)
        count += 1

    """
    # TEST 2
    def test_invalid_num_args(self):
        global cmds
        global infile
        global outfile1
        print("\033[03;33m" + "TEST 1: ### TESTING INVALID NUM OF ARGS" + "\033[0m")
        print()
        count = 1
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                usr_test = f'(./pipex {file1} "{cmd1}" "{cmd2}") 2>errors'
                os.system(usr_test)
                usr_errors_file = open("errors", "r")
                usr_errors = usr_errors_file.read()
                print(
                    "\033[96m" + f'TEST 1 "INVALID NUM OF ARGS" #{count}):' + "\033[0m",
                    usr_test,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                usr_errors_file.close()
                count += 1
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile1
                usr_test = f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2} oof) 2>errors'
                os.system(usr_test)
                usr_errors_file = open("errors", "r")
                usr_errors = usr_errors_file.read()
                print(
                    "\033[96m" + f'TEST 1 "INVALID NUM OF ARGS" #{count}):' + "\033[0m",
                    usr_test,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                usr_errors_file.close()
                count += 1

    def test_invalid_files(self):
        global cmds
        global infile
        global outfile
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = "unipex_files/"
                file2 = outfile
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = "unipex_files/invalid"
                file2 = outfile
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = "unipex_files"
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()

    def test_with_invalid_cmds(self):
        global cmds
        global infile
        global outfile
        new_cmds = [
            "cat",
            "cAt",
            "AS2Gxz -l",
            "CsX3Lm",
            "",
        ]
        for cmd1 in new_cmds:
            for cmd2 in new_cmds:
                file1 = infile
                file2 = outfile
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()

    def test_invalid_order(self):
        global cmds
        global infile
        global outfile
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile
                os.system(f"(< {cmd1} {file1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex "{cmd1}" {file1} "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile
                os.system(f"(< {cmd1} {cmd2} | {file1} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex "{cmd1}" "{cmd2}" {file1} {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile
                os.system(f"(< {file1} {file2} | {cmd1} > {cmd2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} {file2} "{cmd1}" "{cmd2}") 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out = open(f"{file2}", "r").read()
                sys_errors = open("errors", "r").read()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out = open(f"{file2}", "r").read()
                usr_errors = open("errors", "r").read()
                print(
                    "\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m",
                    sys_errors,
                    sep="\n",
                )
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                self.assertEqual(sys_out, usr_out)
                print()
        """
