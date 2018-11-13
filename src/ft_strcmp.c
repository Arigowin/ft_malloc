/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 04:02:49 by dolewski          #+#    #+#             */
/*   Updated: 2018/11/13 04:02:49 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char		*s_one;
	const unsigned char		*s_two;

	s_one = (const unsigned char*)s1;
	s_two = (const unsigned char*)s2;
	while (*s_one == *s_two && *s_one != '\0')
	{
		s_one++;
		s_two++;
	}
	return (*s_one - *s_two);
}
