#ifndef CODEXION_H
# define CODEXION_H

# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct rules
{
	int				coders;
	int				burnout;
	int				compile;
	int				debug;
	int				refactor;
	int				c_required;
	int				cooldown;
	long long		time;
	int				done;
	int				scheduler;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	state_mutex;
}		t_rules;

typedef struct coder	t_coder;

typedef struct dongle
{
	int				id;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				available;
	int				next_owner;
	long long		last_released;
	int				count;
	long long		ready_at;
	t_coder			**queue;
}		t_dongle;

typedef struct coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*l_dongle;
	t_dongle		*r_dongle;
	t_rules			*rules;
	long long		last_compile;
	int				t_compiled;
	pthread_mutex_t	mutex;
}		t_coder;

long		ft_atol(char	*str);
int			has_char(char *str);
int			*parser(char **av);
long long	get_time(void);
int			remove_coder(t_coder **c, int coders);
int			simulation_status(t_rules *r);
void		wait(long long wait_time, t_coder *c);
void		log_it(t_coder *c, char *mssg);
void		fifo(t_dongle *d);
void		edf(t_dongle *d);
void		unlock_dongles(t_coder *c, t_dongle *d);
void		*coder_routine(void *arg);
void		init_dongles(t_rules *r, t_dongle *d);
void		init_coders(t_rules *r, t_dongle *d, t_coder *c, long long time);
void		create_them(int coders, t_coder *c);
void		join_them(int coders, t_coder *c);
void		free_all(int coders, t_dongle *d);
void		initialize(t_rules *r, t_dongle *d, t_coder *c);

#endif