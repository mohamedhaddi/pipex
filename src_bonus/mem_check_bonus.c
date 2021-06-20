/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:20:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 14:15:00 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_and_init(char *ptr, int *state)
{
	free(ptr);
	*state = 0;
}

void	free_double_pointer_and_init(char **ptr, int *state)
{
	int	i;

	i = 0;
	while (ptr[i])
		free_and_init(ptr[i++], state);
	free(ptr);
	*state = 0;
}

void	free_triple_pointer_and_init(char ***ptr, int *state)
{
	int	i;

	i = 0;
	while (ptr[i])
		free_double_pointer_and_init(ptr[i++], state);
	free(ptr);
	*state = 0;
}

void	free_all_arg_data(t_arg_data *arg_data)
{
	if (arg_data->cmds_state)
		free_triple_pointer_and_init(arg_data->cmds, &arg_data->cmds_state);
	if (arg_data->pids_state)
	{
		free(arg_data->pids);
		arg_data->pids_state = 0;
	}
}

void	init_all_arg_data(t_arg_data *arg_data, int argc, char **argv)
{
	int	i;

	arg_data->argv = argv;
	arg_data->cmds_state = 0;
	arg_data->pids_state = 0;
	arg_data->not_cmds = 3;
	if (argc > 2)
		if (ft_strncmp(argv[1], "here_doc", 9) == 0)
			arg_data->not_cmds = 4;
	if (argc < arg_data->not_cmds + 2)
		raise_error(EINVAL, "There should be at least 4 arguments to your " \
			"program (or 5 if you're using here_doc).\nError");
	arg_data->cmds = malloc(sizeof(char ***) * (argc - arg_data->not_cmds + 1));
	check_error(!arg_data->cmds, ENOMEM, "malloc() failed.\nError", arg_data);
	i = 0;
	while (i < argc - arg_data->not_cmds)
	{
		arg_data->cmds[i] = malloc(sizeof(char **) * 4);
		check_error(
			!arg_data->cmds[i], ENOMEM, "malloc() failed.\nError", arg_data);
		arg_data->cmds[i][0] = NULL;
		i++;
	}
	arg_data->cmds[i] = NULL;
	arg_data->cmds_state = 1;
}
