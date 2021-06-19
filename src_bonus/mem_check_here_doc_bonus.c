/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_check_here_doc_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:18:41 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 16:52:24 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_all_here_doc_data(t_here_doc_data *here_doc_data)
{
	if (here_doc_data->input_state)
		free_and_init(here_doc_data->input, &here_doc_data->input_state);
	if (here_doc_data->line_state)
		free_and_init(here_doc_data->line, &here_doc_data->line_state);
	if (here_doc_data->limiter_state)
		free_and_init(here_doc_data->limiter, &here_doc_data->limiter_state);
}

void	init_all_here_doc_data(t_here_doc_data *here_doc_data)
{
	here_doc_data->input_state = 0;
	here_doc_data->line_state = 0;
	here_doc_data->limiter_state = 0;
}
