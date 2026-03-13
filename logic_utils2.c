#include "codexion.h"

int	remove_coder(t_coder **c, int coders)
{
	int	i;
	int	id;

	i = 0;
	id = c[0]->id;
	while (i < coders - 1)
	{
		c[i] = c[i + 1];
		i++;
	}
	return (id);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	simulation_status(t_rules *r)
{
	int	status;

	pthread_mutex_lock(&r->state_mutex);
	status = r->done;
	pthread_mutex_unlock(&r->state_mutex);
	return (status);
}

void	log_it(t_coder *c, char *mssg)
{
	pthread_mutex_lock(&c->rules->log_mutex);
	if (simulation_status(c->rules) == 0)
		printf("%lld %d %s\n", get_time() - c->rules->time, c->id, mssg);
	pthread_mutex_unlock(&c->rules->log_mutex);
}

void	wait(long long wait_time, t_coder *c)
{
	long long	c_time;

	c_time = get_time();
	if (wait_time < c_time)
		return ;
	while (c_time < wait_time)
	{
		if (c->rules->done == 1)
			break ;
		usleep(500);
		c_time = get_time();
	}
}
