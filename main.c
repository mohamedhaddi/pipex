/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 16:50:38 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/05 14:05:55 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	close(0); // release fd 0 so that it no longer refers to any file and may be reused
	(void)argc;
	/*
	if (argc != 5)
	{
		perror("Error\nThere should be five arguments:\n./pipex file1 cmd1 cmd2 file2");
		exit(EXIT_FAILURE);
	}
	*/
	open(argv[1], 'r'); // open file with fd 0

	// child process
	if (fork() == 0)
	{
		char **cmd1 = ft_split(argv[2], ' ');
		// HOW TO GET THE ABSOLUTE PATH
		int i = 0;
		while (envp[i]) {
			char **var = ft_split(envp[i], '=');
			if (ft_strncmp("PATH", var[0], 5) == 0) {
				printf("%s\n", envp[i]);
				char **paths = ft_split(var[1], ':');
				int j = 0;
				int fd = -1;
				while (paths[j] && fd == -1) {
					fd = open(ft_strjoin(paths[j], ft_strjoin("/", cmd1[0])), O_RDONLY);
					if (fd != -1)
						break ;
					j++;
				}
				if (fd != -1)
					printf("Found it! --> %s\n", paths[j]);
				close(fd);
			}
			i++;
		}
		//execvp(cmd1, cmd1);
		//execve(cmd1[0], cmd1, envp); // by default, programs reads from stdin (fd 0)
	}
}
