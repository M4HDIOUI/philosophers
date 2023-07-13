/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omahdiou <omahdiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:05:15 by omahdiou          #+#    #+#             */
/*   Updated: 2023/07/13 06:27:39 by omahdiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo{
	int				id;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				last_meal;
	int				nb_of_meal;
	int				is_eatan;
	int				are_full;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
	pthread_mutex_t	*action;
	pthread_t		philothread;
	struct s_philo	*next;
}	t_philo;

int			ft_isdigit(int c);
int			push_atoi(char *s);
int			parcing(char **av);
int			fill_strct(char **av, t_philo **philo);
t_philo		*ft_ln(char **av, int id, pthread_mutex_t *pt, pthread_mutex_t *dt);
t_philo		*ft_lstlast(t_philo *lst);
void		lst_addback(t_philo **philo, t_philo *new);
void		creat_thread(t_philo *philo);
void		*routine(void *rou);
int			check_death(void *d);
int			check(t_philo *philo);
void		action(int action, t_philo *philo);
void		ft_print(t_philo *philo, char *str);
long long	timeinmilliseconds(void);

#endif
