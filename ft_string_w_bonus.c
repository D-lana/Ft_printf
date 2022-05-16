#include "ft_printf.h"

static void	ft_wch_copy_to_chr(int size_w_ch, const wchar_t *w_ch, char **s2)
{
	int		i;
	char	c;
	char	*s3;

	i = 0;
	c = 0;
	s3 = *s2;
	while (i < size_w_ch)
	{
		c = w_ch[i];
		*s3 = c;
		s3++;
		i++;
	}
	*s2 = s3;
}

static int	ft_string_w_copy(const wchar_t *w_ch, char **s1)
{
	int		i;
	char	c;
	char	*s2;
	int		size_w_ch;

	i = 0;
	c = w_ch[i];
	while (c != '\0')
	{
		i++;
		c = w_ch[i];
	}
	size_w_ch = i + 1;
	s2 = (char *)malloc(sizeof(char) * size_w_ch);
	if (s2 == NULL)
		return (-1);
	ft_wch_copy_to_chr(size_w_ch, w_ch, &s2);
	s2 += '\0';
	s2 = s2 - (sizeof(char) * size_w_ch);
	*s1 = s2;
	free (s2);
	return (0);
}

int	ft_string_w_bonus(const char *s, va_list arg, t_list flags, char **s1)
{
	const wchar_t	*s2;
	int				error;

	if (*s == 's' && flags.lh == 5)
	{
		s2 = va_arg(arg, const wchar_t *);
		if (s2 != NULL)
		{
			error = ft_string_w_copy(s2, &*s1);
			if (error == -1)
				return (-1);
		}
		else
			*s1 = "(null)";
	}
	return (0);
}
