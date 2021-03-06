/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desausag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:26:38 by desausag          #+#    #+#             */
/*   Updated: 2021/07/23 14:59:09 by desausag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int ch)
{
	int	r;

	r = 1;
	if (!(ch >= 48 && ch <= 57))
		r = 0;
	return (r);
}
