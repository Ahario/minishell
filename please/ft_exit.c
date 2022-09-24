/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunglee <sunglee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:05:56 by sunglee           #+#    #+#             */
/*   Updated: 2022/09/23 12:44:51 by lee-sung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"
#include "minishell.h"

void	exit2(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

int count_total(t_arg *head)
{
	int i;
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

void	error_message(char *str)
{
	rl_replace_line("", 1);
	printf ("%s", str);
	g_exit_number = 127;
}


int	ft_atoi_exit(const	char *str)
{
	int	sign;
	int	i;
	unsigned long long	ret;

	sign = 1;
	ret = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && ret <= 9223372036854775808u)
		ret = ret * 10 + (str[i++] - '0');
	if ((ret > 9223372036854775807u && sign == 1) || (ret >= 9223372036854775808u && sign == -1))
	{
		error_message("MINISHELL: exit: ");
		printf ("%s: numeric argument required\n", str);
		g_exit_number = 255;
		exit(255);
	}
	return (sign * ret);
}

void	ft_exit(t_data *data)
{
	int t_cnt;
	int	j;
	char *str;
	t_arg	*head;

	j = 0;
	head = data->cmd;
	t_cnt = count_total(head);
	if (t_cnt > 1)
	{
		head = head->next;
		str = head->ac;
		while(str[j] == ' ')
			j++;
		if (str[j] == '-')
			j++;
		while (ft_isdigit(str[j]))
			j++;
		while(str[j] == ' ')
			j++;
		if(j != (int)ft_strlen(str))
		{
			error_message("MINISHELL: exit: ");
			printf ("%s: numeric argument required\n", str);
			g_exit_number = 255;
			exit(255);
		}
		exit(ft_atoi_exit(head->ac));
	}
	if (t_cnt >= 3)
	{
		error_message("MINISHELL: exit: too many arguments\n");
		g_exit_number = 1;
	}
	else
		exit2();
}

void	exit_C_d(void)
{
	printf ("\033[1A");
	printf ("\033[11C");
	printf (" exit\n");
	exit (EXIT_FAILURE);
}
