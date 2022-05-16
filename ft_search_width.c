#include "ft_printf.h"

static int	ft_atoi_printf(const char *symbol)
{
	int	i;
	int	rezult;

	i = 0;
	rezult = 0;
	while (symbol[i] == '-' || symbol[i] == '0' || symbol[i] == ' ')
		i++;
	while (symbol[i] >= '0' && symbol[i] <= '9')
	{
		if (rezult > INT_MAX / 10)
			return (-1);
		rezult = rezult * 10 + (symbol[i] - '0');
		i++;
	}
	return (rezult);
}

int	ft_search_width(va_list argument, const char **symbol_2)
{
	int			i;
	const char	*symbol_3;

	i = 0;
	symbol_3 = *symbol_2;
	if (*symbol_3 == 42)
	{
		i = va_arg(argument, int);
		symbol_3++;
	}
	if (*symbol_3 >= 48 && *symbol_3 <= 57)
	{
		i = ft_atoi_printf(symbol_3);
		while (*symbol_3 >= 48 && *symbol_3 <= 57)
			symbol_3++;
	}
	*symbol_2 = symbol_3;
	return (i);
}
