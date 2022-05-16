#include "ft_printf.h"

static t_list	ft_width(va_list argument, const char **symbol_2, t_list flags)
{
	const char	*symbol_3;

	symbol_3 = *symbol_2;
	flags.width = ft_search_width(&*argument, &symbol_3);
	if (flags.width < 0)
	{
		flags.fill_in = 1;
		flags.width = -flags.width;
	}
	*symbol_2 = symbol_3;
	return (flags);
}

static t_list	ft_point(va_list argument, const char **symbol_2, t_list flags)
{
	const char	*symbol_3;

	symbol_3 = *symbol_2;
	symbol_3++;
	flags.point = ft_search_width(&*argument, &symbol_3);
	if (flags.point < 0)
		flags.point = -1;
	*symbol_2 = symbol_3;
	return (flags);
}

static t_list	ft_all_flags(const char **symbol_2, t_list flags)
{
	const char	*symb_3;

	symb_3 = *symbol_2;
	while (*symb_3 == '0' || *symb_3 == '-' || *symb_3 == '+' || *symb_3 == ' '
		|| *symb_3 == '#')
	{
		if (*symb_3 == '-')
			flags.fill_in = 1;
		if (*symb_3 == '0' && flags.fill_in != 1)
			flags.fill_in = 0;
		flags = ft_flags_bonus(&symb_3, flags);
		symb_3++;
	}
	*symbol_2 = symb_3;
	return (flags);
}

t_list	ft_search_flags(const char **symbol, va_list argument)
{
	t_list		flags;
	const char	*symbol_2;

	flags.width = 0;
	flags.fill_in = -1;
	flags.point = -1;
	flags.b = 0;
	flags.lh = 0;
	symbol_2 = *symbol;
	flags = ft_all_flags(&symbol_2, flags);
	if (*symbol_2 == 42 || (*symbol_2 >= 48 && *symbol_2 <= 57))
		flags = ft_width(&*argument, &symbol_2, flags);
	if (*symbol_2 == '.')
		flags = ft_point(&*argument, &symbol_2, flags);
	while (*symbol_2 == 'l' || *symbol_2 == 'h')
		flags = ft_flags_lh_bonus(&symbol_2, flags);
	if (*symbol_2 == 36)
		symbol_2++;
	*symbol = symbol_2;
	return (flags);
}
