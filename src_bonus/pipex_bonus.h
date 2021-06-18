/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 18:57:17 by mhaddi            #+#    #+#             */
/*   Updated: 2021/06/18 16:51:56 by mhaddi           ###   ########.fr       */
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

# define MAXINT 2147483647
# define BUFFER_SIZE 32

typedef struct s_strings
{
	char		***cmds;
	int			cmds_state;
	char		**argv;
}				t_strings;

size_t			ft_strlen(const char *s);
char    		*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			**ft_split(char const *s, char c);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char    		*ft_strjoin(char *s1, char *s2);
void			*ft_char_calloc(size_t i);
char			*ft_strcpy(char *dest, const char *src);
void			raise_error(int errno_val, char *error_msg);
void			free_double_pointer_and_init(char **ptr, int *state);
void			free_and_init(char *ptr, int *state);
void			make_children(
					int *outfile_fd,
					t_strings *strings,
					char **envp,
					int argc
					);
void			check_error(
					bool is_error,
					int errno_val,
					char *error_msg,
					t_strings *strings
					);
void			open_files(
					int **fds,
					int argc,
					char **argv,
					t_strings *strings
					);
void			free_all_strings(t_strings *strings);
void			init_all_strings(t_strings *strings, int argc, char **argv);
void			create_pipe(int *pipe_fd, t_strings *strings);
void			set_command(char **dst_cmd, char *cmd, t_strings *strings);
int				get_next_line(int fd, char **line);


#endif
