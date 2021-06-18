/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:20:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 04:13:07 by mhaddi           ###   ########.fr       */
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

void	free_all_strings(t_strings *strings)
{
	if (strings->cmds_state)
		free_triple_pointer_and_init(strings->cmds, &strings->cmds_state);
}

void	init_all_strings(t_strings *strings, int argc, char **argv)
{
	int	i;

	strings->cmds = malloc(sizeof(char ***) * (argc - 2));
	check_error(!strings->cmds, ENOMEM, "malloc() failed.\nerror", strings);
	i = 0;
	while (i < argc - 3)
	{
		strings->cmds[i] = malloc(sizeof(char **) * 4);
		check_error(
			!strings->cmds[i], ENOMEM, "malloc() failed.\nerror", strings);
		strings->cmds[i][0] = NULL;
		i++;
	}
	strings->cmds[i] = NULL;
	strings->cmds_state = 1;
	strings->argv = argv;
}