/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntactic_analysis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 22:32:35 by allefebv          #+#    #+#             */
/*   Updated: 2019/06/14 11:36:08 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_state_s(t_pos *pos, t_tkn *tkn)
{
	if (syntactic_sm[pos->state_s][0] == -2)
		pos->state_s = syntactic_sm[pos->state_s][1];
	if (syntactic_sm[pos->state_s][0] == -3)
		pos->state_s = tkn->op->op_state_s;
}

static int	ft_encode(t_pos *pos, t_tkn *tkn, t_list **lbls, t_bytebf *bytebf)
{
	(void)lbls;
	if (!(bytebuf_realloc(bytebf, pos, tkn)))
		return (ft_error(NULL, e_no_print, NULL, NULL));
	bytecode_gen(tkn, bytebf, pos);
	if (tkn && pos->ocp && tkn->mem_size != 0)
		ocp_create(tkn, pos, bytebf->inst);
	pos->lc_tkn = pos->lc_tkn + tkn->mem_size;
	return (1);
}

int		syntactic_analysis(t_list **lbls, t_pos *pos, t_bytebf *bytebf, t_tkn **tkn)
{
	while (pos->state_s != -1 && pos->buf_pos < pos->size_buf)
	{
		if (!lexical_analysis(pos, tkn, lbls))
			return (ft_error(NULL, e_no_print, NULL, NULL));
		if (pos->multiple_line)
			return (1);
		pos->state_s = syntactic_sm[pos->state_s][(*tkn)->type];
		if (pos->state_s == -1)
			return (ft_error(pos, e_lexical_error, *tkn, NULL));
		if (syntactic_sm[pos->state_s][0] < -1)
			check_state_s(pos, *tkn);
		if ((*tkn)->type == e_lbl || (*tkn)->type == e_op)
			pos->lc_instruction = pos->lc_tkn;
		if (!(ft_encode(pos, *tkn, lbls, bytebf)))
			return (ft_error(NULL, e_no_print, NULL, NULL));
		if (((*tkn)->type == e_ind_label || (*tkn)->type == e_dir_label)
			&& (*tkn)->value == NULL)
			continue ;
		free(*tkn);
	}
	return (1);
}
