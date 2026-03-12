#include "codexion.h"

void	init_dongles(t_rules *r, t_dongle *d)
{
	int	i;

	i = 0;
	while (i < r->coders)
	{
		pthread_mutex_init(&d[i].mutex, NULL);
		pthread_cond_init(&d[i].cond, NULL);
		d[i].available = 1;
		d[i].next_owner = 0;
		d[i].id = i + 1;
		d[i].queue = malloc(r->coders * sizeof(t_coder *));
		if (!d[i].queue)
			return ;
		d[i].ready_at = 0;
		d[i].count = 0;
		i++;
	}
}

void	init_coders(t_rules *r, t_dongle *d, t_coder *c, long long time)
{
	int		i;

	i = 0;
	while (i < r->coders)
	{
		c[i].id = i + 1;
		c[i].t_compiled = 0;
		c[i].l_dongle = &d[i];
		c[i].r_dongle = &d[(i + 1) % r->coders];
		c[i].rules = r;
		c[i].last_compile = time;
		pthread_mutex_init(&c[i].mutex, NULL);
		i++;
	}
}

void	create_them(int coders, t_coder *c)
{
	int	i;

	i = 0;
	while(i < coders)
	{
		pthread_create(&c[i].thread, NULL, coder_routine, &c[i]);
		i++;
	}
}

void	join_them(int coders, t_coder *c)
{
	int i;

	i = 0;
	while(i < coders)
	{
		pthread_join(c[i].thread, NULL);
		i++;
	}
}

void	free_all(int coders, t_dongle *d)
{
	int	i;

	i = 0;
	while (i < coders)
	{
		pthread_cond_destroy(&d[i].cond);
		pthread_mutex_destroy(&d[i].mutex);
		free(d[i].queue);
		i++;
	}
}
