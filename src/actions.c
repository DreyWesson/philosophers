/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:21:57 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 08:18:02 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	philo_eat(t_philo *phi)
{
	pthread_mutex_lock(&phi->data->mymutex[phi->lfork]);
	if (!print_state(phi, phi->id + 1, NONE, FORK))
		return (drop_forks(phi, 1), 0);
	pthread_mutex_lock(&phi->data->mymutex[phi->rfork]);
	if (!print_state(phi, phi->id + 1, NONE, FORK))
		return (drop_forks(phi, 2), 0);
	if (!print_state(phi, phi->id + 1, GREEN, EAT))
		return (drop_forks(phi, 2), 0);
	pthread_mutex_lock(&phi->data->tm);
	phi->t_die = get_time();
	pthread_mutex_unlock(&phi->data->tm);
	time_sim(phi->data->t_eat);
	drop_forks(phi, 2);
	pthread_mutex_lock(&phi->data->shared);
	phi->n_eaten++;
	pthread_mutex_unlock(&phi->data->shared);
	return (1);
}

int	philo_sleep(t_philo *phi)
{
	if (!print_state(phi, phi->id + 1, NONE, SLEEP))
		return (0);
	time_sim(phi->data->t_sleep);
	return (1);
}

int	philo_think(t_philo *phi)
{
	if (!print_state(phi, phi->id + 1, NONE, THINK))
		return (0);
	return (1);
}

int	is_dead(t_philo *phi, int *i)
{
	int time;

	if (*i == phi[*i].data->philo_num)
	{
		*i = 0;
		usleep(200);
	}
	pthread_mutex_lock(&phi->data->tm);
	time = time_diff(phi[*i].t_die);
	if (time > phi[*i].data->t_die)
	{
		pthread_mutex_unlock(&phi->data->tm);
		print_state(&phi[*i], phi[*i].id + 1, RED, DIED);
		pthread_mutex_lock(&phi->data->shared);
		phi[*i].data->philo_died = 1;
		pthread_mutex_unlock(&phi->data->shared);
		return (1);
	}
	pthread_mutex_unlock(&phi->data->tm);
	*i = *i + 1;
	return (0);
}