/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <desausag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:03:54 by desausag          #+#    #+#             */
/*   Updated: 2021/07/16 10:49:32 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
** Returns 0 if c is not digit or alpha. Else returns ascii index of c
** @param c
** @return
*/

int		ft_isalnum(int c)
{
	int i;

	i = 0;
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		i = 1;
	return (i);
}
