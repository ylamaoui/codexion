#include "codexion.h"

void	fifo(t_dongle *d)
{
	int	id;

	id = remove_coder(d->queue, d->count);
	d->count -= 1;
	d->next_owner = id;
	pthread_cond_signal(&d->cond);
}

static void	c_remove(t_coder **c, int id, int coders)
{
	int	i;
	int	j;

	i = 0;
	while (i < coders)
	{
		if (c[i]->id == id)
		{
			j = i;
			while (j < coders - 1)
			{
				c[j] = c[j + 1];
				j++;
			}
		}
		i++;
	}
}

static t_coder	*lowest_time(t_coder **c, int coders)
{
	int			i;
	int			smallest;
	int			burnout;
	long long	deadline;
	t_coder		*tmp;

	i = 0;
	burnout = c[i]->rules->burnout;
	smallest = c[i]->last_compile + burnout;
	tmp = c[i];
	while (i < coders)
	{
		deadline = c[i]->last_compile + burnout;
		if (deadline < smallest)
		{
			smallest = deadline;
			tmp = c[i];
		}
		i++;
	}
	return (tmp);
}

void	edf(t_dongle *d)
{
	t_coder	*chosen;

	chosen = lowest_time(d->queue, d->count);
	c_remove(d->queue, chosen->id, d->count);
	d->count -= 1;
	d->next_owner = chosen->id;
	pthread_cond_broadcast(&d->cond);
}

void	unlock_dongles(t_coder *c, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	if (d->count == 0)
		d->available = 1;
	else
	{
		if (c->rules->scheduler == 1)
			fifo(d);
		else
			edf(d);
	}
	d->ready_at = get_time() + c->rules->cooldown;
	pthread_mutex_unlock(&d->mutex);
}
