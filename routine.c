/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omahdiou <omahdiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:18:07 by omahdiou          #+#    #+#             */
/*   Updated: 2023/07/13 06:29:00 by omahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timeinmilliseconds(void)
{
	struct timeval	tv;
	long			current_time;
	static long		start;

	gettimeofday(&tv, NULL);
	current_time = (((long long)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
	if (!start)
		start = current_time;
	return (current_time - start);
}

void	ft_print(t_philo *philo, char *str)
{
	int	time;

	time = 0;
	pthread_mutex_lock(philo->print);
	time = timeInMilliseconds();
	printf("%d philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(philo->print);
}

void	action(int action, t_philo *philo)
{
	long	begin;

	begin = timeInMilliseconds();
	pthread_mutex_lock(philo->death);
	while (timeInMilliseconds() - begin < action)
	{
		pthread_mutex_unlock(philo->death);
		usleep(100);
		pthread_mutex_lock(philo->death);
	}
	pthread_mutex_unlock(philo->death);
	return ;
}

int	check(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (timeInMilliseconds() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

int	check_death(void *d)
{
	int		how_many;
	t_philo	*philo;

	philo = (t_philo *)d;
	how_many = philo->number_of_philosophers;
	while (1)
	{
		if (check(philo) == 1)
			return (philo->id);
		while (philo->number_of_times_each_philosopher_must_eat != -1 && philo->number_of_times_each_philosopher_must_eat == 0)
		{
			how_many--;
			if (how_many == 0)
				return (0);
			philo = philo->next;
		}
		how_many = philo->number_of_philosophers;
		philo = philo->next;
	}
	usleep(100);
	return (-1);
}

void	*routine(void *rou)
{
	t_philo	*philo;

	philo = (t_philo *)rou;
	if (philo->id % 2 == 1)
		usleep(philo->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(philo->fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->next->fork);
		ft_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->death);
		philo->last_meal = timeInMilliseconds();
		pthread_mutex_unlock(philo->death);
		ft_print(philo, "is eating");
		philo->number_of_times_each_philosopher_must_eat--;
		action(philo->time_to_eat, philo);
		pthread_mutex_unlock(philo->fork);
		pthread_mutex_unlock(philo->next->fork);
		ft_print(philo, "is sleeping");
		action(philo->time_to_sleep, philo);
		ft_print(philo, "is thinking");
	}
	return (NULL);
}
