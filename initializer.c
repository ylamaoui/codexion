#include "codexion.h"

static int reached_max(int coders, t_coder *c)
{
	int	i;
	int check;
	int	compiles;

	i = 0;
	check = 0;
	while (i < coders)
	{
		pthread_mutex_lock(&c[i].mutex);
		compiles = c[i].t_compiled;
		pthread_mutex_unlock(&c[i].mutex);
		if (compiles >= c[i].rules->c_required)
			check++;
		i++;
	}
	if (check == coders)
		return (1);
	return (0);
}

void  *superviser_routine(void *arg)
{
	int	i;
	int	num;
	long long last_time;
	int	check;
	t_coder *c;

	c = (t_coder *)arg;
	num = c[0].rules->coders;	
	while (1)
	{
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&c[i].mutex);
			last_time = get_time() - c[i].last_compile;
			pthread_mutex_unlock(&c[i].mutex);
			check = reached_max(num, c);
			if ((last_time > c[i].rules->burnout) || check == 1)
			{
				pthread_mutex_lock(&c[i].rules->state_mutex);
				c[i].rules->done = 1;
				pthread_mutex_unlock(&c[i].rules->state_mutex);
				if (check == 1)
					printf("All coders compiled successfully\n");
				else
					printf("%lld %d %s\n", get_time() - c[i].rules->time, c[i].id, "burned out");
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
}

void	initialize(t_rules *r, t_dongle *d, t_coder *c)
{
	struct timeval	tv;
	pthread_t	sup;

	gettimeofday(&tv, NULL);
	pthread_mutex_init(&r->log_mutex, NULL);
	pthread_mutex_init(&r->state_mutex, NULL);
	init_dongles(r, d);
	r->time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	init_coders(r, d, c, r->time);
	create_them(r->coders, c);
	pthread_create(&sup, NULL, superviser_routine, c);
	join_them(r->coders, c);
	pthread_join(sup, NULL);
	pthread_mutex_destroy(&r->log_mutex);
	pthread_mutex_destroy(&r->state_mutex);
	free_all(r->coders, d);
}
