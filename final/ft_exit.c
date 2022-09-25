/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:05:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/25 17:00:52 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

void	exit2(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int	count_total(t_arg *head)
{
	int		i;
	t_arg	*tem;

	i = 0;
	tem = head;
	while (tem != NULL)
	{
		i++;
		tem = tem->next;
	}
	return (i);
}

void	error_message(char *str, char *des)
{
	char *error;

	error = "MINISHELL:";
	if (str)
		error = ft_strjoin_normal(error, str);
	if (des)
		error = ft_strjoin_flag(error, des, 1);
	rl_replace_line(error, 1);
	g_exit_number = 127;
}

int	ft_atoi_exit(char *str, int i)
{
	int					sign;
	unsigned long long	ret;

	sign = 1;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9' && ret <= 9223372036854775808u)
		ret = ret * 10 + (str[i++] - '0');
	if ((ret > 9223372036854775807u && sign == 1) \
			|| (ret > 9223372036854775808u && sign == -1))
	{
		printf ("exit\n");
		error_message("exit: ", "numeric argument required\n");
		ft_putstr_fd(" numeric argument required\n", 2);
		g_exit_number = 255;
		exit(255);
	}
	return (sign * ret);
}

static void	exit_numeric_check(char *str)
{
	int	j;

	j = 0;
	while (str[j] == ' ')
		j++;
	if (str[j] == '-' || str[j] == '+')
		j++;
	while (ft_isdigit(str[j]))
		j++;
	while (str[j] == ' ')
		j++;
	if (j != (int)ft_strlen(str))
	{
		printf("exit\n");
		error_message("exit: ", "numeric argument required\n");
		ft_putstr_fd(" numeric argument required\n", 2);
		g_exit_number = 255;
		exit(255);
	}
}

void	ft_exit(t_data *data)
{
	int		t_cnt;
	char	*str;
	t_arg	*head;

	head = data->cmd;
	t_cnt = count_total(head);
	if (t_cnt > 1)
	{
		head = head->next;
		str = head->ac;
		exit_numeric_check(str);
		exit(ft_atoi_exit(head->ac, 0));
	}
	if (t_cnt >= 3)
	{
		error_message("exit: ", "too many arguments\n");
		g_exit_number = 1;
	}
	else
		exit2();
}

void	exit_c_d(void)
{
	printf ("\033[1A");
	printf ("\033[11C");
	printf (" exit\n");
	exit (EXIT_FAILURE);
}
