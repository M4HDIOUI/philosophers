/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omahdiou <omahdiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 13:27:52 by omahdiou          #+#    #+#             */
/*   Updated: 2023/07/13 06:11:57 by omahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creat_thread(t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= philo->number_of_philosophers)
	{
		pthread_create(&philo->philothread, NULL, &routine, philo);
		philo = philo->next;
		pthread_detach(philo->philothread);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		dead;

	philo = malloc(sizeof(t_philo *));
	dead = 0;
	if (ac == 5 || ac == 6)
	{
		if (parcing(av))
		{
			printf("Error !");
			return (1);
		}
		fill_strct(av, &philo);
		creat_thread(philo);
		dead = check_death(philo);
		if (dead != 0)
			printf("%llu philo %d is died\n", timeInMilliseconds(), dead);
	}
	else
	{
		printf("%s", "Error : bad arg\n");
		return (1);
	}
}
