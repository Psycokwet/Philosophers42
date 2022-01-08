/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/08 16:29:40 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"
#include <unistd.h>

static int	ft_putnbr_str_int(int n, char *s, int *i)
{
	if (n < 10)
	{
		s[(*i)++] = n + '0';
		s[(*i)] = '\0';
	}
	else
	{
		ft_putnbr_str_int(n / 10, s, i);
		ft_putnbr_str_int(n % 10, s, i);
	}
}

int	ft_putnbr_str(int n, char *s)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		if (n - 1 > 0)
		{
			ft_putnbr_str_int((-(n + 1) / 10), s, &i);
			ft_putnbr_str_int((-((n + 1) % 10) + 1), s, &i);
		}
		else
			ft_putnbr_str_int(-n, s, &i);
	}
	else
		ft_putnbr_str_int(n, s, &i);
	return (i);
}
/*
** #1. L'integer a ecrire.
** #2. Le file descriptor sur lequel ecrire.
** Valeur de retour None
** Fonctions externes autorisees
** write
** Description Ecrit l'integer 'n' sur le file descriptor donne.
*/
