void			ft_bzero(void *s, int n)
{
	int				i;
	char			*tmp;

	i = 0;
	tmp = s;
	while (tmp && i < n)
	{
		*tmp = '\0';
		i++;
		tmp++;
	}
}
