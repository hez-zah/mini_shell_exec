#include "mini_shell.h"

t_pip	*ft_lstnew_pip(char *arg, int index)
{
	t_pip	*new;

	new = NULL;
	new = (t_pip *)malloc(sizeof(t_pip));
	if (!new)
		return (NULL);
    new->pip_arg = ft_split(arg, ' ');
    if (ft_check_cmd_arg(new->pip_arg[0]) && new->pip_arg[0])
        new->cmd = ft_strdup(new->pip_arg[0]);
    if (ft_check_cmd_arg(new->pip_arg[1]) && new->pip_arg[1])
        new->arg_cmd = ft_strdup(new->pip_arg[1]);
    new->pip_infile = 0;
    new->pip_outfile = 1;
    new->index = index;
	return (new);
}

t_pip	*last_add_pip(t_pip *head, char *arg, int index)
{
	t_pip	*b;
	t_pip	*tmp;

	b = ft_lstnew_pip(arg, index);
	if (!head)
		head = b;
	else
	{
		tmp = head;
		while (tmp->next_pip)
			tmp = tmp->next_pip;
		tmp->next_pip = b;
	}
	return (head);
}

t_pip	*make_pip(t_pip *head, char *arg, int index)
{
	return (last_add_pip(head, arg, index));
}