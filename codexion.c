#include "codexion.h"

void	set_them(t_rules *rules, int *nums, char **av, int ac)
{
	rules->coders = nums[0];
	rules->burnout = nums[1];
	rules->compile = nums[2];
	rules->debug = nums[3];
	rules->refactor = nums[4];
	rules->c_required = nums[5];
	rules->cooldown = nums[6];
	rules->done = 0;
	if (strcmp(av[ac - 1], "fifo") == 0)
		rules->scheduler = 1;
	else
		rules->scheduler = 0;
}

void	free_them(t_rules *r, t_coder *c, t_dongle *d)
{
	if (r)
		free(r);
	if (c)
		free(c);
	if (d)
		free(d);
}

int	main(int ac, char **av)
{
	t_rules	*p;
	t_dongle	*d;
	t_coder	*c;
	int			*nums;

	if (ac != 9 || av[1][0] == '0')
		return (1);
	if (strcmp(av[ac - 1], "fifo") != 0 && strcmp(av[ac - 1], "edf") != 0)
		return (1);
	nums = parser(av);
	if (!nums)
		return (1);
	p = malloc(sizeof(t_rules));
	if (!p)
		return (1);
	set_them(p, nums, av, ac);
	d = malloc(p->coders * sizeof(t_dongle));
	c = malloc(p->coders * sizeof(t_coder));
	if (!c || !d)
	{
		free_them(p, c, d);
		return (1);
	}
	initialize(p, d, c);
	free_them(p, c, d);
	free(nums);
}
