#include "../mini_shell.h"

t_cmd	*ft_lstnew_cmd(char *cmd, char *arg_cmd, int index)
{
	t_cmd	*new;

	new = NULL;
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
    new->cmd = ft_strdup(cmd);
	if (ft_check_cmd_arg(arg_cmd))
    	new->cmd_arg = ft_strdup(arg_cmd);
	return (new);
}

t_cmd	*last_add_cmd(t_cmd *head, char *cmd, char *arg_cmd, int index_cmd)
{
	t_cmd	*b;
	t_cmd	*tmp;

	b = ft_lstnew_cmd(cmd , arg_cmd, index_cmd);
	if (!head)
		head = b;
	else
	{
		tmp = head;
		while (tmp->next_cmd)
			tmp = tmp->next_cmd;
		tmp->next_cmd = b;
	}
	return (head);
}

t_cmd	*creat_cmd(t_cmd	*head, char *cmd, char *arg_cmd, int index_cmd)
{
	return (last_add_cmd(head, cmd, arg_cmd, index_cmd));
}