/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngwch <youngwch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:07:28 by youngwch          #+#    #+#             */
/*   Updated: 2022/11/17 11:08:22 by youngwch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char    *ft_strmapi(char const *s, char(*f)(unsigned int, char))
{
    char            *answer;
    unsigned int    i;
    
    answer = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!answer)
        return (NULL);
    i = 0;
    while (i < ft_strlen(s))
    {
        answer[i] = f(i, s[i]);
        i++;
    }
    return (answer);
}