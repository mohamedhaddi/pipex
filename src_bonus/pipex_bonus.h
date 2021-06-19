/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/19 16:52:19 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	pid_t		*pids;
	int			pids_state;
	char		**argv;
	int			not_cmds;
}				t_arg_data;

typedef struct s_here_doc_data
{
	char		*input;
	int			input_state;
	char		*line;
	int			line_state;
	char		*limiter;
	int			limiter_state;
}				t_here_doc_data;

size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			*ft_char_calloc(size_t i);
char			*ft_strcpy(char *dest, const char *src);
void			raise_error(int errno_val, char *error_msg);
void			free_double_pointer_and_init(char **ptr, int *state);
void			free_and_init(char *ptr, int *state);
void			make_children(
					int *outfile_fd,
					t_arg_data *arg_data,
					char **envp,
					int argc);
void			check_error(bool is_error,
					int errno_val,
					char *error_msg,
					t_arg_data *arg_data);
void			check_error_here_doc(int *error_data,
					char *error_msg,
					t_here_doc_data *here_doc_data,
					t_arg_data *arg_data);
void			open_files(int **fds, int argc, t_arg_data *arg_data);
void			free_all_arg_data(t_arg_data *arg_data);
void			free_all_here_doc_data(t_here_doc_data *here_doc_data);
void			init_all_arg_data(t_arg_data *arg_data, int argc, char **argv);
void			init_all_here_doc_data(t_here_doc_data *here_doc_data);
void			create_pipe(int *pipe_fd, t_arg_data *arg_data);
void			set_command(char **dst_cmd, char *cmd, t_arg_data *arg_data);
char			*ft_getline(void);

#endif
