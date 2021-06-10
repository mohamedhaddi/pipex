/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/10 17:40:39 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <unistd.h>

typedef struct s_strings
{
	char		**first_cmd;
	int			first_cmd_state;
	char		**second_cmd;
	int			second_cmd_state;
}				t_strings;

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			raise_error(int errno_val, char *error_msg);
void			free_double_pointer_and_init(char **ptr, int *state);
void			free_and_init(char *ptr, int *state);
void			make_children(
					int *pipe_fd,
					int *outfile_fd,
					t_strings *strings,
					char **envp
					);
void			check_error(
					bool is_error,
					int errno_val,
					char *error_msg,
					t_strings *strings
					);
void			open_files(
					int *infile_fd,
					int *outfile_fd,
					char **argv,
					t_strings *strings
					);
void			free_all_strings(t_strings *strings);
void			init_all_strings(t_strings *strings);
void			create_pipe(int *pipe_fd, t_strings *strings);
void			set_command(char **dst_cmd, char *cmd, t_strings *strings);

#endif
