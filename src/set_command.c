/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:32:22 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 13:16:11 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Setting up the final command that will be fed to execve(), so that instead of
 * giving execve() the command itself and then parsing its arguments (e.g. if a
 * user's second command was "grep ' '" or "grep \\\\\\\\" a lot of parsing and
 * escaping would have to be done), instead, I'm giving execve() the binary
 * "/bin/sh" with the first argument being "-c" and the second argument being
 * the user's command with all its arguments in a single string, so "/bin/sh"
 * will do all the parsing and of course the exact behavior we want.
 */
void	set_command(char **dst_cmd, char *cmd, t_strings *strings)
{
	size_t	cmd_len;

	cmd_len = ft_strlen(cmd) + 1;
	dst_cmd[0] = malloc(sizeof(char *) * 8);
	check_error(dst_cmd[0] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[0], "/bin/sh", 8);
	dst_cmd[1] = malloc(sizeof(char *) * 3);
	check_error(dst_cmd[1] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[1], "-c", 3);
	dst_cmd[2] = malloc(sizeof(char *) * cmd_len);
	check_error(dst_cmd[2] == NULL, ENOMEM, "malloc() failed.\nError", strings);
	ft_strlcpy(dst_cmd[2], cmd, cmd_len);
	dst_cmd[3] = NULL;
}
