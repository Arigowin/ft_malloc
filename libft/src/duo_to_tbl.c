/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duo_to_tbl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avacher <avacher@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:59:59 by avacher           #+#    #+#             */
/*   Updated: 2015/11/29 16:27:42 by avacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			duo_count(t_duo *lst)
{
	int			cpt;

	cpt = 0;
	while (lst)
	{
		lst = lst->next;
		cpt++;
	}
	return (cpt);
}

char		**duo_to_tbl(t_duo *lst, char *sep)
{
	int			i;
	char		*tmp1;
	char		*tmp2;
	char		**tbl;

	i = 0;
	if ((tbl = (char **)malloc(sizeof(char *) * (duo_count(lst) + 1))) == NULL)
		return (NULL);
	while (lst != NULL)
	{
		tmp1 = ft_properjoin(lst->name, sep);
		if (lst->type == ENV || lst->type == LOCAL)
			tmp2 = ft_properjoin(tmp1, lst->value);
		else
			tmp2 = ft_properjoin(tmp1, lst->tmp_val);
		if ((tbl[i] = ft_strdup(tmp2)) == NULL)
			return (NULL);
		free(tmp1);
		free(tmp2);
		lst = lst->next;
		i++;
	}
	tbl[i] = NULL;
	return (tbl);
}
