/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 07:59:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/12 16:16:28 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

int	check_value(char chess_board[], int index, int queen_row)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (queen_row == (chess_board[i] - '0'))
			return (0);
		if (i - index == (chess_board[i] - '0') - queen_row
			|| index - i == (chess_board[i] - '0') - queen_row)
			return (0);
		i ++;
	}
	return (1);
}

void	dfs(char chess_board[], int index, int *count)
{
	int	queen_row;

	queen_row = 0;
	if (index == 10)
	{
		*count = *count + 1;
		write(1, chess_board, 10);
		write(1, "\n", 1);
		return ;
	}
	while (queen_row < 10)
	{
		if (check_value(chess_board, index, queen_row))
		{
			chess_board[index] = queen_row + '0';
			dfs(chess_board, index + 1, count);
		}
		queen_row ++;
	}
	return ;
}

int	ft_ten_queens_puzzle(void)
{
	int		i;
	char	chess_board[10];
	int		count;

	i = 0;
	count = 0;
	while (i < 10)
	{
		chess_board[i] = 'F';
		i ++;
	}
	dfs(chess_board, 0, &count);
	return (count);
}
