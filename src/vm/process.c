/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:17:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/06/08 22:47:33 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int count_alivechamps(t_game *game, t_champ **champs)
{
	int i;
	int end;
	int win;

	win = 1;
	end = 0;
	i = 0;
	while (i < game->nbr_champs)
	{
		ft_printf("checking champ\n");
		if ((*champs + i)->live_c)
		{
			end++;
			win = (*champs + i)->id;
		}
		i++;
	}
	if (!end || end == 1)
		return (win);
	i = 0;
	while ((*champs + i))
	{
		if ((*champs + i)->live_c)
			champs[i]->live_c = 0;
		i++;
	}
	return (0);
}

static int is_end(t_game *game, t_champ **champs, t_list **prcs)
{
	t_list *cur;
	t_list *pre;

	cur = *prcs;
	pre = NULL;
	while (cur)
	{
		if (((t_process *)(cur->content))->is_alive)
		{
			((t_process *)(cur->content))->is_alive = 0;
			pre = (!pre) ? cur: pre->next;
			cur = cur->next;
			continue;
		}
		ft_lstsub(prcs, cur);
		ft_lstdel(&cur, &del_lstprcs);
		cur = (!pre) ? *prcs : pre->next;
		pre = (cur == *prcs) ? NULL : pre->next;
	}
	game->cycle_to_die -= CYCLE_DELTA;
	game->cycle_d = game->cycle_to_die;
	return (count_alivechamps(game, champs));
}

int process(t_game *game)
{
	t_list *cur;
	t_process *p;

	ft_printf("cycle %i\n", game->cycle);
	if (!game->cycle_d && is_end(game, &(game->champs[0]), &(game->prcs)))
		return (1);
	cur = game->prcs;
	while (cur)
	{
		p = (t_process *)(cur->content);
		if (!p->wait_c)
			prcs_inst(game, (t_process *)(cur->content));
		else
			p->wait_c -= 1;
		cur = cur->next;
	}
	game->cycle += 1;
	game->cycle_d -= 1;
	return (0);
}
