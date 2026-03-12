#include "codexion.h"

static void	lock_dongle(t_coder *c, t_dongle *d)
{
	long long	wait_cooldown;
	pthread_mutex_lock(&d->mutex);
	if (d->available == 1)
	{
		d->available = 0;
		wait_cooldown = d->ready_at;
	}
	else
	{
		d->queue[d->count] = c;
		d->count++;
		while(d->available == 0 && d->next_owner != c->id)
			pthread_cond_wait(&d->cond, &d->mutex);
		d->available = 0;
		d->next_owner = 0;
		wait_cooldown = d->ready_at;
	}
	pthread_mutex_unlock(&d->mutex);
	if (wait_cooldown > get_time())
		wait(wait_cooldown, c);
	log_it(c, "has taken a dongle");

}

static void	compile(t_coder *c)
{
	pthread_mutex_lock(&c->mutex);
	c->last_compile = get_time();
	c->t_compiled++;
	pthread_mutex_unlock(&c->mutex);
	log_it(c, "is compiling");
	wait(get_time() + c->rules->compile, c);
}

static void	debugg(t_coder *c)
{
	log_it(c, "is debugging");
	wait(get_time() + c->rules->debug, c);
}

static void refactor(t_coder *c)
{
	log_it(c, "is refactoring");
	wait(get_time() + c->rules->refactor, c);
}

void	*coder_routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	while(simulation_status(c->rules) == 0)
	{
		if (c->id % 2 == 0)
		{
			lock_dongle(c, c->l_dongle);
			lock_dongle(c, c->r_dongle);
		}
		else
		{
			lock_dongle(c, c->r_dongle);
			lock_dongle(c, c->l_dongle);
		}
		compile(c);
		unlock_dongles(c, c->l_dongle);
		unlock_dongles(c, c->r_dongle);
		debugg(c);
		refactor(c);
	}
	return (NULL);
}
