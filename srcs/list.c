/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najimehdi <najimehdi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 09:42:38 by najimehdi         #+#    #+#             */
/*   Updated: 2020/04/27 14:15:21 by najimehdi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_lst_ls	*init_listls(void)
{
	t_lst_ls *lst;

	lst = (t_lst_ls*)ft_memalloc(sizeof(t_lst_ls));
	return (lst);
}

int			isempty_lstls(t_lst_ls *lst)
{
	if (lst->next == NULL && lst->prv == NULL && lst->read == NULL)
		return (1);
	return (0);
}

void		add_node(t_lst_ls *lst, struct dirent *read)
{
	t_lst_ls *new_node;
	t_lst_ls *tmp;

	if (isempty_lstls(lst))
		lst->read = read;
	else
	{
		tmp = lst;
		while (tmp->next)
			tmp = tmp->next;
		new_node = (t_lst_ls*)ft_memalloc(sizeof(t_lst_ls));
		new_node->read = read;
		new_node->prv = tmp;
		tmp->next = new_node;
	}
}

void		clear_lstls(t_lst_ls *lst)
{
	if (lst)
	{
		go_to_front(&lst);
		while (lst)
		{
			free(lst->prv);
			lst->prv = NULL;
			if (!lst->next)
				break ;
			lst = lst->next;
		}
		free(lst);
		lst = NULL;
	}
}

void		print_lstls(t_lst_ls *lst)
{
	t_lst_ls	*tmp;
	struct stat *buff;

	tmp = lst;
	while (tmp)
	{
		buff = get_stat(tmp->read->d_name);
		ft_printf("%-10s %s", tmp->read->d_name, ctime(&buff->ST_MTIME.tv_sec));
		ft_printf("d_reclin = %d\n", buff->st_blocks);
		tmp = tmp->next;
		free(buff);
	}
}
