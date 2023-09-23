/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:19:38 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 08:15:59 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	int	i;

	data->philo_died = 0;
	data->philo_num = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_eat = ft_atoi(argv[5]);
	else
		data->n_eat = -1;
	if (!data->philo_num || !data->t_die || !data->t_eat || !data->t_sleep
		|| (argc == 6 && !data->n_eat))
		return (printf("Error: some arguments are zero or out bound\n"), 0);
	data->mymutex = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->mymutex)
		return (printf("Error: memory allocation failed\n"), 0);
	i = 0;
	while (i < data->philo_num)
		if (pthread_mutex_init(data->mymutex + i++, NULL))
			return (printf("Error: failed to initialise mutex\n"), 0);
	if (pthread_mutex_init(&data->print, NULL))
		return (printf("Error: failed to initialise mutex\n"), 0);
	return (1);
}

void	init_philo(t_philo *phi, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		phi[i].id = i;
		phi[i].n_eaten = 0;
		phi[i].t_die = 0;
		phi[i].lfork = i;
		phi[i].rfork = (i + 1) % data->philo_num;
		phi[i].data = data;
		i++;
	}
	phi[i].t_die = 0;
	phi[i].n_eaten = 0;
	phi[i].data = data;
}

void	drop_forks(t_philo *phi, int flag)
{
	pthread_mutex_unlock(&phi->data->mymutex[phi->lfork]);
	if (flag == 2)
		pthread_mutex_unlock(&phi->data->mymutex[phi->rfork]);
}