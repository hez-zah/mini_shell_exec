/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_patht.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hez-zahi <hez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 13:20:10 by hez-zahi          #+#    #+#             */
/*   Updated: 2023/03/18 01:36:38 by hez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	free_split(char **s, char **s1)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	i = 0;
	while (s1[i])
	{
		free(s1[i]);
		i++;
	}	
}

char	*ft_patht(char *cmd, char **env)
{
	int		k;
	int		i ;
	char	**led;
	char	**ten;
	char	*sp;

	k = 0;
	while (ft_strncmp(env[k], "PATH=", 5))
		k++;
	if (!cmd)
		return (NULL);
	led = ft_split(env[k] + 5, ':');
	ten = ft_split(cmd, ' ');
	i = 0;
	while (led[i])
	{
		sp = ft_strjoin(led[i], ten[0]);
		if (access(sp, F_OK) == 0)
		{
			free_split(led, ten);
			return (sp);
		}
		free(sp);
		i++;
	}
	free_split(led, ten);
	return (NULL);
}
