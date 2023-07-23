/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bounus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hez-zahi <hez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 23:17:32 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/03/18 01:35:43 by hez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_pip	*init_pip(t_pip *pip)
{
	t_pip	*tmp;
	int			fd[2];

	tmp = pip;
	while (tmp->next_pip)
	{
		if (pipe(fd) < 0)
			perror("error");
		if (tmp->index == 0)
			tmp->pip_in = tmp->pip_outfile;
		tmp->next_pip->pip_in = fd[0];
		tmp->pip_out = fd[1];
		tmp = tmp->next_pip;
	}
	tmp->pip_out = 1;
	return (pip);
}

void	child_pip(t_pip *pip, char **env)
{
	pid_t	pid;
	char	*led;

	pid = fork();
	if (!pid)
	{
		if (pip->pip_in > 1)
			dup2(pip->pip_in, 0);
		if (pip->pip_out > 1)
			dup2(pip->pip_out, 1);
		redir_pip(pip, env);
		if (pip->pip_in == 1)
		{
			led = get_next_line(pip->pip_in);
			while (led)
			{
				write(pip->pip_out, led, ft_strlen(led));
				led = get_next_line(pip->pip_in);
			}
		}
		exit(0);
	}
	if (pip->pip_in > 1)
		close(pip->pip_in);
	if (pip->pip_out > 1)
		close(pip->pip_out);
}

t_pip	*child_process_pip(t_pip *pip, char **env)
{
	int			i;
	int			j;
	t_pip		*dmp;
	dmp = pip;
	i = 0;
	while (dmp)
	{
		child_pip(dmp, env);
		dmp = dmp->next_pip;
		i++;
	}
	j = 0;
	while (j < i)
	{
		waitpid(0, NULL, 0);
		j++;
	}
	return (pip);
}

void	app_redir(t_pip *pip, char **env)
{
	init_pip(pip);
	pip = child_process_pip(pip, env);
}

int	main(int ac, char *av[], char **env)
{
	t_shell	shell;
	t_pip   *pip;
	if (ac >= 1)
	{
		init_arg(&shell, ac, av);
		pipe_redir(&shell);
		pip = shell.pip;
		herdoc(pip, env);
		app_redir(pip, env);
	}
	return (0);
}
