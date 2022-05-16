#include "ft_printf.h"

t_list	ft_flags_lh_bonus(const char **symbol_2, t_list flags)
{
	const char	*symb_3;

	symb_3 = *symbol_2;
	if (*symb_3 == 'l')
		flags.lh = 5;
	if (*symb_3 == 'h')
		flags.lh = 7;
	symb_3++;
	if (*symb_3 == 'l' && flags.lh == 5)
	{
		flags.lh = 6;
		symb_3++;
	}
	if (*symb_3 == 'h' && flags.lh == 7)
	{
		flags.lh = 8;
		symb_3++;
	}
	*symbol_2 = symb_3;
	return (flags);
}
