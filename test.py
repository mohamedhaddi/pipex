# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.py                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 17:22:00 by mhaddi            #+#    #+#              #
#    Updated: 2021/06/08 17:43:31 by mhaddi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import os

result_stderr = os.popen("(< infile cdat | grep x > outfile) 2>&1").read()
result_outfile = open("outfile", "r").read()
print(result_stderr, end="")
print(result_outfile, end="")
