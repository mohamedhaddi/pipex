/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:20:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 10:09:35 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
}

void	init_all_arg_data(t_arg_data *arg_data, int argc)
{
	int	i;

	arg_data->cmds = malloc(sizeof(char ***) * (argc - 2));
	check_error(!arg_data->cmds, ENOMEM, "malloc() failed.\nerror", arg_data);
	i = 0;
	while (i < argc - 3)
	{
		arg_data->cmds[i] = malloc(sizeof(char **) * 4);
		check_error(
			!arg_data->cmds[i], ENOMEM, "malloc() failed.\nerror", arg_data);
		arg_data->cmds[i][0] = NULL;
		i++;
	}
	arg_data->cmds[i] = NULL;
	arg_data->cmds_state = 1;
}
