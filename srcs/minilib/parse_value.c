/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/27 18:20:29 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	parse_value(char const *arg, int *result)
{
	int				tmp;
	char			*checker;
	unsigned int	checker_length;

	if (arg == NULL)
		return (-EXIT_FAILURE);
	tmp = ft_atoi(arg);
	checker = ft_itoa(tmp);
	checker_length = ft_strlen(checker);
	if (!(ft_strncmp(arg, checker, checker_length) == 0 && ft_strlen(arg)
			== checker_length))
	{
		free(checker);
		return (-EXIT_FAILURE);
	}
	free(checker);
	*result = tmp;
	return (EXIT_SUCCESS);
}
