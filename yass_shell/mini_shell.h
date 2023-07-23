/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hez-zahi <hez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:10:34 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/03/18 01:33:46 by hez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define ERR_ARG "nombre d'argumet invalude"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_cmd
{
	char			*cmd;
	char			*cmd_arg;
	struct s_cmd	*next_cmd;
}t_cmd;

typedef struct s_limit
{
	char			*limit;
	int				index_limit;
	struct s_limit	*next_limit;	
}t_limit;

typedef struct s_pip
{
	char			**pip_arg;
	char			*cmd;
	char			*arg_cmd;
	t_limit			*limit;
	int				fd_red[2];
	int				permi;
	int				herd_in;
	int				herd_out;
	// int				access;
	int				pip_infile;
	int				pip_outfile;
	int				pip_in;
	int				pip_out;
	int				index;
	struct s_pip	*next_pip;
}t_pip;


typedef struct s_shell
{
	char			**arg;
	// char			**pip_arg;
	t_pip			*pip;
	t_cmd			*cmd1;
	// t_limit			*limit;
	int				infile;
	int				outfile;
	int				fd_red[2];
	int				fd_pipe[2];
	struct s_pip_bo	*next;
}t_shell;

char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
size_t		ft_strlen1(const char *s);
char		*ft_concat(char const *s1, char const *s2);

char		*patht(char *cmd, char **env);
char		*ft_patht(char *cmd, char **env);
t_limit		*creat_linkdlist(t_limit	*head, char *limit, int index);

char		*get_next_line(int fd);
char		*ft_strjoin1(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*copy(char *txt, char *save, int i);
char		*conc(char *stash, char *buf);

void		init_arg(t_shell *shell, int ac, char **av);
void		init_limit(t_pip *pip);
void		child_1(char **env, t_pip *pip);
void		child_2(char **env, t_pip *pip);
void		affich(t_pip *pip, char **env);
void		creat_pipe(t_pip *pip);
void		file_redric(t_pip *pip);

void		redir_pip(t_pip *pip, char **env);
void		herdoc(t_pip *pip, char **env);

int			ft_check_cmd_arg(char *str);
int			check_herdoc(char **arg);
void		pipe_redir(t_shell *shell);


t_pip		*make_pip(t_pip *head, char *arg, int index);
void		redir_pip(t_pip *pip, char **env);
int			creat_file1(char *filename, int lo_method);
int			check_infile_herd(char **str);
#endif
