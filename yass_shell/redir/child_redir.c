#include "../mini_shell.h"

int	ft_check_cmd_arg(char *str)
{
	if (!str || !ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">", 1) || !ft_strncmp(str, "", 1))
		return (0);
	return (1);
}

int		check_infile_herd(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strncmp(str[i], "<<", 2) && str[i + 1])
			return (1);
	return (0);
}

void	aid_file_red_pip(t_pip *pip)
{
	if (!ft_strncmp(pip->pip_arg[0], "<", 1) && pip->pip_arg[1])
		pip->pip_infile = creat_file1(pip->pip_arg[1], 0);
	else if (!ft_strncmp(pip->pip_arg[0], ">>", 2) && pip->pip_arg[1])
		pip->pip_outfile = creat_file1(pip->pip_arg[1], 2);
	else if (!ft_strncmp(pip->pip_arg[0], ">", 1) && pip->pip_arg[1])
		pip->pip_outfile =  creat_file1(pip->pip_arg[1], 1);
}

void	file_red_pip(t_pip *pip, char **env)
{
	int i;
	int	k;

	i = 0;
	aid_file_red_pip(pip);
	while (pip->pip_arg[++i])
	{
		if (!ft_strncmp(pip->pip_arg[i], "<<", 2))
			continue;
		else if (!ft_strncmp(pip->pip_arg[i], "<", 1) && pip->pip_arg[i + 1])
			pip->pip_infile = creat_file1(pip->pip_arg[i + 1], 0);
		else if (!ft_strncmp(pip->pip_arg[i], ">>", 2) && pip->pip_arg[i + 1])
			pip->pip_outfile = creat_file1(pip->pip_arg[i + 1], 2);
		else if (!ft_strncmp(pip->pip_arg[i], ">", 1) && pip->pip_arg[i + 1])
			pip->pip_outfile =  creat_file1(pip->pip_arg[i + 1], 1);
	}
}

void	child_red_pip(char **env, t_pip  *pip)
{
	char	**l;
	char	*cont;
	int		status;
	pid_t pid;

	cont = ft_concat(pip->cmd, pip->arg_cmd);
	l = ft_split(cont, ' ');
	pid = fork();
	if (!pid)
	{
		if (check_infile_herd(pip->pip_arg))
			dup2(pip->herd_in, 0);
		else if (pip->pip_infile > 0)
			dup2(pip->pip_infile, 0);
		if (pip->pip_outfile != 1)
			dup2(pip->pip_outfile, 1);
		if (ft_patht(pip->cmd, env) && pip->cmd)
			execve(ft_patht(pip->cmd, env), l, env);
		else
			write(2, "command not fond\n", 18);
	}
	if (check_infile_herd(pip->pip_arg))
		close(pip->herd_in);
	else if (pip->pip_infile > 0)
		close(pip->pip_infile);
	if (pip->pip_outfile != 1)
		close(pip->pip_outfile);
	waitpid(pid, &status, 0);
}

void	redir_pip(t_pip *pip, char **env)
{
	file_red_pip(pip, env);
	child_red_pip(env, pip);
}