/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omahdiou <omahdiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:10:49 by omahdiou          #+#    #+#             */
/*   Updated: 2023/07/13 06:10:16 by omahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	push_atoi(char *s)
{
	int		i;
	long	numb;
	int		sign;

	numb = 0;
	i = 0;
	sign = 1;
	if (s[i] && (s[i] == '+' || s[i] == '-'))
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		numb = (numb * 10) + (s[i] - 48);
		i++;
	}
	numb = numb * sign;
	return ((int)numb);
}

int	parcing(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
		}
		i++;
	}
	return (0);
}

int	fill_strct(char **av, t_philo **philo)
{
	int				i;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;

	death = malloc (sizeof(pthread_mutex_t));
	print = malloc (sizeof(pthread_mutex_t));
	pthread_mutex_init(death, NULL);
	pthread_mutex_init(print, NULL);
	*philo = ft_lstnew(av, 1, print, death);
	i = 1;
	while (i < (*philo)->number_of_philosophers)
	{
		lst_addback(philo, ft_lstnew(av, i + 1, print, death));
		i++;
	}
	ft_lstlast(*philo)->next = *philo;
	return (0);
}
