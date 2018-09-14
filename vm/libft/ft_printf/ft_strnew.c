/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:39:27 by amichak           #+#    #+#             */
/*   Updated: 2017/10/30 15:39:30 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "handle_printf.h"

char	*ft_strnew(size_t size)
{
	char	*r;

	if (!(r = (char *)malloc(sizeof(*r) * (size + 1))))
		return (NULL);
	return (ft_memset(r, 0, size + 1));
}
