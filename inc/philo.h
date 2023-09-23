/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doduwole <doduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:44:36 by doduwole          #+#    #+#             */
/*   Updated: 2023/09/23 08:17:27 by doduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define NONE "\033[0m"

typedef struct s_data
{
	int				philo_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				philo_died;
	long long		time;
	pthread_t		monitor;
	pthread_mutex_t	*mymutex;
	pthread_mutex_t	shared;
	pthread_mutex_t	tm;
	pthread_mutex_t	print;
}					t_data;

typedef struct s_philo
{
	int				id;
	long long		t_die;
	int				n_eaten;
	int				lfork;
	int				rfork;
	pthread_t		th;
	t_data			*data;
}					t_philo;

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died"

typedef enum e_args
{
	PHILO_NUM = 1,
	DEATH_TIME = 2,
	EAT_TIME = 3,
	SLEEP_TIME = 4,
	MEAL_NUM = 5

}					t_args;
/**
 * UTILS FUNCTIONS
 */
int					ft_error(char *message);
int					is_digit(char *str);
int					ft_atoi(const char *str);
/**
 * HELPER FUNCTIONS
 */
int					validator(int argc, char **argv);
int					validate_value(long val, t_args type);
/**
 * INIT FUNCTIONS
 */
int					init_data(t_data *data, char **argv, int argc);
void				drop_forks(t_philo *phi, int flag);
void				init_philo(t_philo *phi, t_data *data);
void				routine_helper2(t_philo *phi);
void				routine_helper1(t_philo *phi);
void				routine2_helper2(t_philo *phi);
void				routine2_helper1(t_philo *phi);
int					print_state(t_philo *phi, int id, char *color, char *status);
long long			get_time(void);
long long			time_diff(long long time);
void				time_sim(long long time);
void				free_all(t_data *data, t_philo *phi);

int					is_dead(t_philo *phi, int *i);
int					philo_sleep(t_philo *phi);
int					philo_eat(t_philo *phi);
int					philo_think(t_philo *phi);
int					philo_sleep(t_philo *phi);
void				*routine(void *arg);
int					simulation(t_philo *phi);
int					th_create(t_philo *phi);
void				*routine2(void *args);

#endif