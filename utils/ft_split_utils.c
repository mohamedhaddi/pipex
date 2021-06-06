/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 16:31:07 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/06 19:08:07 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ternary_rep_for_rowlen(
			int condition, size_t i, size_t *row_len, size_t *len_calc)
{
	if (condition)
		row_len[i - 1] = *len_calc;
	else
		row_len[i - 1] = *len_calc + 1;
}

void	ternary_rep_for_lencalc(int condition, size_t *len_calc)
{
	if (condition)
		*len_calc = *len_calc + 1;
	else
		*len_calc = *len_calc;
}

void	*free_and_return_null(void *row_len)
{
	free(row_len);
	return (NULL);
}

void	*free_twodim_str_and_return_null(char **arr, size_t size)
{
	size_t	i;	

	i = 0;
	while (i < size)
		free(arr[i++]);
	return (free_and_return_null(arr));
}
