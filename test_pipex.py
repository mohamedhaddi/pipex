# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_pipex.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:46:22 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/08 17:45:32 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import unittest
import os


class TestPipex(unittest.TestCase):
    def test_pipex(self):
        result_stderr = os.popen("(< infile cdat | grep x > outfile) 2>&1").read()
        result_outfile = open("outfile", "r").read()
        result_infile = open("infile", "r").read()
