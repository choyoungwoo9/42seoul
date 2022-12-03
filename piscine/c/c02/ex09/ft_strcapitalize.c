/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 10:56:21 by youngwch          #+#    #+#             */
/*   Updated: 2022/10/11 11:01:29 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_word(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	else if (ch >= 'a' && ch <= 'z')
		return (1);
	else if (ch >= 'A' && ch <= 'Z')
		return (1);
	return (0);
}

int	count_and_capitalize_word(char *str)
{
	int	i;

	if (*str >= 'a' && *str <= 'z')
		*str = *str + ('A' - 'a');
	i = 1;
	while (is_word(*(str + i)))
	{
		if (*(str + i) >= 'A' && *(str + i) <= 'Z')
			*(str + i) = *(str + i) + ('a' - 'A');
		i ++;
	}
	return (i);
}

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (is_word(*(str + i)))
		{
			i = i + count_and_capitalize_word(str + i);
		}
		i ++;
	}	
	return (str);
}
