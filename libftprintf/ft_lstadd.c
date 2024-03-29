/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:40:02 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/26 16:24:29 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_lstadd(t_list **alst, t_list *new)
{
	if (!new || !alst)
		return (0);
	new->next = *alst;
	*alst = new;
	return (1);
}
