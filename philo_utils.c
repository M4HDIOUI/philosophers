/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omahdiou <omahdiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:10:49 by omahdiou          #+#    #+#             */
/*   Updated: 2023/07/13 06:17:42 by omahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_ln(char **av, int id, pthread_mutex_t *pt, pthread_mutex_t *dt)
{
	pthread_mutex_t	*fork;
	t_philo			*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	fork = malloc(sizeof(pthread_mutex_t));
	if (!new)
		return (0);
	new->id = id;
	new->number_of_philosophers = push_atoi(av[1]);
	new->time_to_die = push_atoi(av[2]);
	new->time_to_eat = push_atoi(av[3]);
	new->time_to_sleep = push_atoi(av[4]);
	if (av[5])
		new->number_of_times_each_philosopher_must_eat = push_atoi(av[5]);
	else
		new->number_of_times_each_philosopher_must_eat = -1;
	pthread_mutex_init(fork, NULL);
	new->fork = fork;
	new->death = dt;
	new->print = pt;
	(new)->next = 0;
	return (new);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	while (lst)
	{
		if (!(lst)->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	lst_addback(t_philo **philo, t_philo *new)
{
	t_philo	*temp;

	if (philo)
	{
		if (!(*philo))
			(*philo) = new;
		else
		{
			temp = ft_lstlast(*philo);
			temp->next = new;
		}
	}
}
