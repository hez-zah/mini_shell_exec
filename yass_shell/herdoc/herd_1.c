#include "../mini_shell.h"

void	init_arg(t_shell *shell, int ac, char **av)
{
	char		*led;
	char		*led_old;
	int			i;
	i = 1;
	led = ft_strdup(av[i]);
	while (++i < ac)
	{
		led_old = led;
		led = ft_concat(led, av[i]);
		free(led_old);
	}
	shell->arg = ft_split(led, '|');
}

void init_limit(t_pip *pip)
{
	int		i;
	int		j;

	j = 0;
	pip->limit = NULL;
	while (pip)
	{
		i = 0;
		while (pip->pip_arg[i])
		{
			if (!ft_strncmp(pip->pip_arg[i], "<<", 2) && pip->pip_arg[i + 1])
			{
				pip->limit = creat_linkdlist(pip->limit, pip->pip_arg[i + 1], j);
				j++;
			}
			i++;
		}
		pip = pip->next_pip;
	}
}
