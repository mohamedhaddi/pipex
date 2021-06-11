import unittest
import os

"""
Can't use assertEqual for errors since user error messages
might be (in most cases) different than system error messages.

If you don't want to compare errors comment out these two lines:
# print("\033[91m" + "SYSTEM ERROR MSGS:" + "\033[0m", sys_errors, sep="\n")
# print("\033[91m" + "YOUR ERROR MSGS:" + "\033[0m", usr_errors, sep="\n")
"""

if not os.path.exists("unipex_files"):
    os.makedirs("unipex_files")

infile = open("unipex_files/infile", "w+")

"""
Change your input file here:
"""

infile.write('hi\n \
             cv?\n \
             test space\n \
             test/slash\n \
             test\\backslash\n')

cmds = []

class unipex(unittest.TestCase):
    def test_invalid_num_args(self):
        outfile = "unipex_files/outfile"
        os.system(f"(./pipex {infile} {cmd1} {cmd2} {outfile}) 2>errors")
        usr_out = open(f"{outfile}", "r").read()
        usr_errors = open("errors", "r").read()
        print("\033[91m" + "YOUR ERROR MSGS:" + "\033[0m", usr_errors, sep="\n")
    def test_invalid_files(self):
    def test_invalid_args(self):
    def test_invalid_files_and_args(self):
    def test_invalid_order(self):
        os.system(f"(< {infile} {cmd1} | {cmd2} > {outfile}) 2>errors")
        sys_out = open(f"{outfile}", "r").read()
        sys_errors = open("errors", "r").read()
        os.system(f"(./pipex {infile} {cmd1} {cmd2} {outfile}) 2>errors")
        usr_out = open(f"{outfile}", "r").read()
        usr_errors = open("errors", "r").read()
        self.assertEqual(sys_out, usr_out)
        print("\033[91m" + "SYSTEM ERROR MSGS:" + "\033[0m", sys_errors, sep="\n")
        print("\033[91m" + "YOUR ERROR MSGS:" + "\033[0m", usr_errors, sep="\n")


if __name__ == "__main__":
    unittest.main()
