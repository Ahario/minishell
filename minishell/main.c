#include "minishell.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[j] != '\0')
		j++;
	if (dstsize == 0)
		return (j);
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

int	check(char const str, char *charset)
{
	if (str == charset[0])
		return (1);
	return (0);
}

int	findsecond(char const *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(check(str[i], charset)))
		i++;
	return (i);
}

int	findfirst(char const *str, char *charset)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (*str)
	{
		while (*str && check(*str, charset))
			str++;
		i = findsecond(str, charset);
		str += i;
		if (i)
			total++;
	}
	return (total);
}

char	**malloc_free(char **all)
{
	int	i;

	i = 0;
	while (all[i])
	{
		free(all[i]);
		i++;
	}
	free(all);
	return (NULL);
}

char	**ft_split(char const *s, char *c)
{
	int		i;
	int		total;
	char	**dest;

	i = 0;
	if (!s)
		return (NULL);
	total = findfirst(s, c);
	dest = (char **)malloc(sizeof(char *) * (total + 1));
	if (!dest)
		return (0);
	while (i < total)
	{
		while (check(*s, c))
			s++;
		dest[i] = malloc(sizeof(char) * (findsecond(s, c) + 1));
		if (!dest[i])
			return (malloc_free(dest));
		ft_strlcpy(dest[i], s, findsecond(s, c) + 1);
		s += findsecond(s, c);
		i++;
	}
	dest[total] = 0;
	return (dest);
}

void parse(char *ch)
{
	int			i;
	char **str;

	str = ft_split(ch, " ");
	i = 0;

	while (str[i] != NULL)
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void before_init(void)
{
	struct termios	change;

	tcgetattr(STDIN_FILENO, &change);
	change.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &change);
}

int	main(int argc, char *argv[], char **evnp)
{
	t_data			*data;
	struct termios	terminal;
	char *ch;
	int idx = -1;
	tcgetattr(STDIN_FILENO, &terminal);
	before_init();
	while(1)
	{
		ch = readline("MINISHELL./ ");
//		sunglee_singla_here;
		if (ch)
			parse(ch);
		add_history(ch);
		free(ch);
		
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
	return (0);
}

