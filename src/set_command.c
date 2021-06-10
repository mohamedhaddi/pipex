/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:32:22 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:33:02 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
