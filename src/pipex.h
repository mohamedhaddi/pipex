/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/20 14:02:50 by mhaddi           ###   ########.fr       */
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

typedef struct s_arg_data
{
	char		***cmds;
	int			cmds_state;
}				t_arg_data;

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
					int *outfile_fd,
					t_arg_data *arg_data,
					char **envp
					);
void			check_error(
					bool is_error,
					int errno_val,
					char *error_msg,
					t_arg_data *arg_data
					);
void			open_files(
					int *infile_fd,
					int *outfile_fd,
					char **argv,
					t_arg_data *arg_data
					);
void			free_all_arg_data(t_arg_data *arg_data);
void			init_all_arg_data(t_arg_data *arg_data, int argc);
void			create_pipe(int *pipe_fd, t_arg_data *arg_data);
void			set_command(char **dst_cmd, char *cmd, t_arg_data *arg_data);

#endif
