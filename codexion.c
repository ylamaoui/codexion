#include "codexion.h"


static long	ft_atol(char	*str)
{
	long (sign), (result);
	sign = 1;
	result = 0;
	if (!str || str[0] == '\0')
		return (-1);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	while (*str && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (result * sign < INT_MIN || result * sign > INT_MAX)
		return (-1);
	else
		return (result * sign);
}


static void free_it(int **list)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static int *parser(char **av)
{
    int i;
	int	j;
	int num;
	int	*p;

	i = 1;
	j = 0;
	p = malloc(7 * sizeof(int));
	if (!p)
	{
		free(p);
		return(NULL);
	}
	while(av[i] && i != 8)
    {
        num = ft_atol(av[i]);
        if (num < 0)
		{
            free_it(&p);
			return (NULL);
		}
		p[j] = num;
		j++;
		i++;
    }
	return p;
}

void set_them(t_rule **rules, char **av)
{
	
}
int main(int ac, char **av)
{
    t_rule	*p;
	int	*nums;
	int	i;

	i = 0;
	if (ac != 9)
		return (1);
	if (!strcmp(av[ac - 1], "fifo") && !strcmp(av[ac - 1], "edf"))
		return (1);
	p = malloc(sizeof(t_rule));
	if (!p)
		return (1);
	nums = parser(av);

	free(p);
	free(nums);
}