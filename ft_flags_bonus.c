#include "ft_printf.h"

t_list	ft_flags_bonus(const char **symbol_2, t_list flags)
{
	const char	*symb_3;

	symb_3 = *symbol_2;
	if (*symb_3 == '#')
		flags.b = 1;
	else if (*symb_3 == '+')
		flags.b = 2;
	else if (*symb_3 == ' ' && flags.b != 2)
		flags.b = 3;
	return (flags);
}
