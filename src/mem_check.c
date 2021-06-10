/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 17:20:31 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:36:17 by mhaddi           ###   ########.fr       */
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

void	free_all_strings(t_strings *strings)
{
	if (strings->first_cmd_state)
		free_double_pointer_and_init(strings->first_cmd,
			&strings->first_cmd_state);
	if (strings->second_cmd_state)
		free_double_pointer_and_init(strings->second_cmd,
			&strings->second_cmd_state);
}

void	init_all_strings(t_strings *strings)
{
	strings->first_cmd = malloc(sizeof(char **) * 4);
	check_error(
		strings->first_cmd == NULL, ENOMEM, "malloc() failed.\nerror", strings);
	strings->first_cmd_state = 1;
	strings->second_cmd = malloc(sizeof(char **) * 4);
	check_error(
		strings->second_cmd == NULL, ENOMEM, "malloc() failed.\nerror", strings);
	strings->second_cmd_state = 1;
}
