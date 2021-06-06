/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 18:32:52 by mhaddi            #+#    #+#             */
/*   Updated: 2021/05/23 17:38:46 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	*free_and_return_null(void *row_len);
void	*free_twodim_str_and_return_null(char **arr, size_t size);
void	ternary_rep_for_lencalc(int condition, size_t *len_calc);
void	ternary_rep_for_rowlen(
			int condition, size_t i, size_t *row_len, size_t *len_calc);

char	**arrays_filler(
		char const *s, size_t *indxs, size_t *row_len, size_t clmns)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**arr;

	i = 0;
	arr = malloc(sizeof(char *) * (clmns + 1));
	if (!arr)
		return (NULL);
	while (i < clmns)
	{
		j = 0;
		arr[i] = malloc(sizeof(char) * row_len[i]);
		if (!arr[i])
			return (free_twodim_str_and_return_null(arr, i));
		k = indxs[i];
		while (j < row_len[i] - 1)
			arr[i][j++] = s[k++];
		arr[i++][j] = '\0';
	}
	arr[clmns] = NULL;
	return (arr);
}

char	**edgecases(char const *s, char c)
{
	char	**empty_arr;

	if (!c && *s)
	{
		empty_arr = malloc(sizeof(char *) * 2);
		if (!empty_arr)
			return (NULL);
		empty_arr[1] = NULL;
		empty_arr[0] = ft_strdup(s);
		if (!empty_arr[0])
		{
			free(empty_arr);
			return (NULL);
		}
		return (empty_arr);
	}
	empty_arr = malloc(sizeof(char *));
	if (!empty_arr)
		return (NULL);
	empty_arr[0] = NULL;
	return (empty_arr);
}

size_t	columns_counter(char const *s, char c)
{
	size_t	clmns;
	size_t	j;

	clmns = 0;
	j = 0;
	if (s[0] != c && s[0] != '\0')
		clmns = 1;
	while (s[j])
	{
		if (s[j] == c && s[j + 1] != c)
		{
			if (s[j + 1] == '\0')
				break ;
			clmns++;
		}
		j++;
	}
	return (clmns);
}

void	storers(char const *s, char c, size_t *indxs, size_t *row_len)
{
	size_t	len_calc;
	size_t	i;
	size_t	j;

	len_calc = 0;
	i = 0;
	if (s[0] != c)
		indxs[i++] = 0 + len_calc++;
	j = 0;
	while (s[j])
	{
		if (s[j] == c && s[j + 1] != c)
		{
			if (s[j + 1] == '\0')
				break ;
			indxs[i] = j + 1;
			if (i > 0)
				row_len[i - 1] = len_calc + 1;
			len_calc = 1;
			i++;
		}
		ternary_rep_for_lencalc(s[j] != c && s[j + 1] != c, &len_calc);
		j++;
	}
	ternary_rep_for_rowlen(!s[j], i, row_len, &len_calc);
}

char	**ft_split(char const *s, char c)
{
	size_t	clmns;
	size_t	*indxs;
	size_t	*row_len;
	char	**arr;

	if (!s)
		return (NULL);
	clmns = columns_counter(s, c);
	if (!c || !clmns)
		return (edgecases(s, c));
	row_len = malloc(sizeof(size_t) * clmns);
	if (!row_len)
		return (NULL);
	indxs = malloc(sizeof(size_t) * clmns);
	if (!indxs)
		return (free_and_return_null(row_len));
	storers(s, c, indxs, row_len);
	arr = arrays_filler(s, indxs, row_len, clmns);
	free(indxs);
	free(row_len);
	if (!arr)
		return (NULL);
	return (arr);
}
