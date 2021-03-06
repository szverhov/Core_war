/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 17:47:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/18 17:47:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

static int	get_arg(t_proc *p, unsigned char *m, unsigned int op[3],
	unsigned int opcode)
{
	int	ok;

	ok = checkarg(opcode, T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG);
	op[0] = get_v_acb(opcode, m, p, 2);
	if (IS_REG(opcode) && IS_REGOK(op[0]))
		op[0] = p->regs[op[0] - 1];
	else if (IS_REG(opcode))
		ok--;
	opcode <<= 2;
	op[1] = get_v_acb(opcode, m, p, 2);
	if (IS_IND(opcode))
		get_val_for_ind(&op[0], m, p, 1);
	else if (IS_REG(opcode) && IS_REGOK(op[1]))
		op[1] = p->regs[op[1] - 1];
	else if (IS_REG(opcode))
		ok--;
	opcode <<= 2;
	op[2] = get_v_acb(opcode, m, p, 2);
	if (IS_REG(opcode) && IS_REGOK(op[2]))
		op[2] = p->regs[op[2] - 1];
	else if (IS_REG(opcode))
		ok--;
	return (ok);
}

void		handle_sti(unsigned char *m, t_proc *p, t_flags fl)
{
	unsigned int	op[3];
	int				addr;
	int				ok;
	unsigned int	opcode;

	p->pc_old = p->pc;
	opcode = m[(p->pc + 1) % MEM_SIZE];
	p->pc = (p->pc + 2) % MEM_SIZE;
	ok = get_arg(p, m, op, opcode);
	if (ok == 3)
	{
		addr = ((p->pc_old + (short)(op[1] + op[2]) % IDX_MOD) % MEM_SIZE);
		if (addr < 0)
			addr += MEM_SIZE;
		set_val_for_mem(m, op[0], addr);
		if (fl.v)
			update_visual(m, (unsigned int)addr, p, 4);
	}
}
