import unittest
import os

"""
    - Can't use `assertEqual()` for errors since user error messages
    might be (in most cases) different than system error messages.
    
    - If you don't want to compare errors comment out these two lines:
    # print("\033[96m" + "SYSTEM TEST'S ERROR MSGS:" + "\033[0m", sys_errors, sep="\n")
    # print("\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m", usr_errors, sep="\n")
    
    - Doesn't check memory leaks.
"""

if not os.path.exists("unipex_files"):
    os.makedirs("unipex_files")

inp_file = open("unipex_files/infile", "w+")

"""
    Change your input file here:
"""

inp_file.write(
    "hi\n \
             cv?\n \
             test space\n \
             test/slash\n \
             test\\backslash\n"
)

inp_file.close()

infile = "unipex_files/infile"
outfile = "unipex_files/outfile"

"""
    Add commands you want to test here:
"""

cmds = [
    "cat",
    "ls -l",
    "wc",
    "grep ' '",
]


class unipex(unittest.TestCase):
    def test_valid_args(self):
        global cmds
        global infile
        global outfile
        count = 1
        print("\033[03;33m" + "### TEST VALID ARGS" + "\033[0m")
        print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                print("\033[03;33m" + f"# TEST {count}:" + "\033[0m")
                print()
                count += 1
                file1 = infile
                file2 = outfile
                os.system(f"(< {file1} {cmd1} | {cmd2} > {file2}) 2>errors")
                sys_out_file = open(file2, "r")
                sys_errors_file = open("errors", "r")
                sys_out = sys_out_file.read()
                sys_errors = sys_errors_file.read()
                sys_out_file.close()
                sys_errors_file.close()
                os.system(f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2}) 2>errors')
                usr_out_file = open(file2, "r")
                usr_errors_file = open("errors", "r")
                usr_out = usr_out_file.read()
                usr_errors = usr_errors_file.read()
                usr_out_file.close()
                usr_errors_file.close()
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

    """
    def test_invalid_num_args(self):
        global cmds
        global infile
        global outfile
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                test_str = f'(./pipex {file1} "{cmd1}" "{cmd2}") 2>errors'
                os.system(test_str)
                usr_errors = open("errors", "r").read()
                print("\033[1m" + "TEST:" + "\033[0m", test_str, sep="\n")
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                print()
        for cmd1 in cmds:
            for cmd2 in cmds:
                file1 = infile
                file2 = outfile
                test_str = f'(./pipex {file1} "{cmd1}" "{cmd2}" {file2} oof) 2>errors'
                os.system(test_str)
                usr_errors = open("errors", "r").read()
                print("\033[1m" + "TEST:" + "\033[0m", test_str, sep="\n")
                print(
                    "\033[96m" + "YOUR TEST'S ERROR MSGS:" + "\033[0m",
                    usr_errors,
                    sep="\n",
                )
                print()

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


if __name__ == "__main__":
    unittest.main()
