import os
import filecmp
import difflib
import time

"""
    - Doesn't check memory leaks.
    - Doesn't print errors for valid arguments tests.
    - Only prints errors for invalid arguments tests (doesn't print output files).
"""

if not os.path.exists("unipex_files"):
    os.makedirs("unipex_files")

inp_file = open("unipex_files/infile", "w+")

"""
    Change your input file here:
"""

inp_content = "hi\n" + "cv?\n" + "test space\n" + "test/slash\n" + "test\\backslash\n"

inp_file.write(inp_content)
inp_file.close()
infile = "unipex_files/infile"
outfile1 = "unipex_files/outfile1"
outfile2 = "unipex_files/outfile2"

"""
    Add commands you want to test here:
"""

cmds = [
    "cat",
    "cAt",
    "grep ' '",
]


print("\033[03;33m" + "TEST I ### VALID ARGS ###" + "\033[0m")
print()
count = 1
for cmd1 in cmds:
    for cmd2 in cmds:
        inp = infile
        out1 = outfile1
        out2 = outfile2
        sys_test = f"(< {inp} {cmd1} | {cmd2} > {out1}) 2>errors1"
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2}) 2>errors2'
        os.system(sys_test)
        time.sleep(0.5)
        os.system(usr_test)
        time.sleep(0.5)
        print(
            "\033[96m" + f"TEST I.{count}: " + "-" * 50 + "\033[0m",
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
            usr_errors_file = open("errors2", "r")
            usr_errors = usr_errors_file.read()
            print(
                "\033[96m" + "YOUR ERROR MSGS:" + "\033[0m",
                usr_errors,
                sep="\n",
            )
        count += 1

print("\033[03;33m" + "TEST II ### INVALID NUM OF ARGS ###" + "\033[0m")
print()
count = 1
for cmd1 in cmds:
    for cmd2 in cmds:
        inp = infile
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}") 2>errors2'
        os.system(usr_test)
        time.sleep(0.5)
        usr_errors_file = open("errors2", "r")
        usr_errors = usr_errors_file.read()
        print(
            "\033[96m" + f"TEST II.{count}: " + "-" * 50 + "\033[0m",
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
for cmd1 in cmds:
    for cmd2 in cmds:
        inp = infile
        out1 = outfile1
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out1} oof) 2>errors2'
        os.system(usr_test)
        time.sleep(0.5)
        usr_errors_file = open("errors2", "r")
        usr_errors = usr_errors_file.read()
        print(
            "\033[96m" + f"TEST II.{count}: " + "-" * 50 + "\033[0m",
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


print("\033[03;33m" + "TEST III ### INVALID FILES ###" + "\033[0m")
print()
count = 1
for cmd1 in cmds:
    for cmd2 in cmds:
        inps = ["unipex_files/", "unipex_files/invalid"]
        for inp in inps:
            out1 = outfile1
            out2 = outfile2
            sys_test = f"(< {inp} {cmd1} | {cmd2} > {out1}) 2>errors1"
            usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2}) 2>errors2'
            os.system(sys_test)
            time.sleep(0.5)
            os.system(usr_test)
            time.sleep(0.5)
            sys_errors = open("errors1", "r").read()
            usr_errors = open("errors2", "r").read()
            print(
                "\033[96m" + f"TEST III.{count}: " + "-" * 50 + "\033[0m",
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
            count += 1
for cmd1 in cmds:
    for cmd2 in cmds:
        inp = infile
        out1 = "unipex_files/"
        out2 = "unipex_files/"
        sys_test = f"(< {inp} {cmd1} | {cmd2} > {out1}) 2>errors1"
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2}) 2>errors2'
        os.system(sys_test)
        time.sleep(0.5)
        os.system(usr_test)
        time.sleep(0.5)
        sys_errors = open("errors1", "r").read()
        usr_errors = open("errors2", "r").read()
        print(
            "\033[96m" + f"TEST III.{count}: " + "-" * 50 + "\033[0m",
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
        count += 1

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
        sys_test = f"(< {inp} {cmd1} | {cmd2} > {out1}) 2>errors1"
        usr_test = f'(./pipex {inp} "{cmd1}" "{cmd2}" {out2}) 2>errors2'
        os.system(sys_test)
        time.sleep(0.5)
        os.system(usr_test)
        time.sleep(0.5)
        sys_errors = open("errors1", "r").read()
        usr_errors = open("errors2", "r").read()
        print(
            "\033[96m" + f"TEST IV.{count}: " + "-" * 50 + "\033[0m",
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
        count += 1

"""
test_invalid_order(self):
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
