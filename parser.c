#include "codexion.h"

long	ft_atol(char	*str)
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

int	has_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	*parser(char **av)
{
	int		*p;
	long	num;
	int		i;
	int		j;

	i = 1;
	j = 0;
	p = malloc(7 * sizeof(int));
	if (!p)
	{
		free(p);
		return (NULL);
	}
	while (av[i] && i != 8)
	{
		num = ft_atol(av[i]);
		if (has_char(av[i]) || num < 0)
		{
			free(p);
			return (NULL);
		}
		p[j++] = num;
		i++;
	}
	return (p);
}
