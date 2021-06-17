/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 17:14:44 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/17 15:16:12 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_check_new_line(char *line)
{
	if (!line)
		return (0);
	while (*line != '\0')
	{
		if (*line == '\n')
			return (1);
		line++;
	}
	return (0);
}

void	ft_free(char **str)
{
	free(*str);
	*str = NULL;
}

int	ft_final_line(char **str, char **line)
{
	int		i;
	char	*tmp;
	char	*temp2;

	i = 0;
	tmp = *str;
	temp2 = *line;
	while (*(*str + i) != '\n')
		i++;
	*line = ft_substr(*str, 0, i);
	*str = ft_strdup(*str + i + 1);
	if (**str == '\0')
		ft_free(str);
	free(temp2);
	free(tmp);
	return (1);
}

static void	init(int *state, char **str)
{
	*state = 1;
	if (!*str)
		*str = ft_char_calloc(1);
}

int	get_next_line(int fd, char **line)
{
	static char	*str;
	int			state;
	char		*tmp;

	init(&state, &str);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > MAXINT || !line)
		return (-1);
	*line = malloc(BUFFER_SIZE + 1);
	if (!(*line))
		return (-1);
	while (state > 0 && !ft_check_new_line(str))
	{
		state = read(fd, *line, BUFFER_SIZE);
		if (state < 0)
			return (-1);
		*(*line + state) = '\0';
		str = ft_strjoin(str, *line);
	}
	if (state > 0)
		return (ft_final_line(&str, line));
	tmp = *line;
	*line = ft_strdup(str);
	free(tmp);
	ft_free(&str);
	return (0);
}
