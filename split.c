/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaouhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 02:37:05 by dhaouhao          #+#    #+#             */
/*   Updated: 2020/02/11 03:12:07 by dhaouhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_get_tab_size(char **tab)
{
	int	index;

	index = 0;
	while (tab[index] != '\0')
		index++;
	return (index);
}

void	ft_free_tab(char **tab)
{
	int	index;

	index = ft_get_tab_size(tab);
	while (--index >= 0)
		free(tab[index]);
	free(tab);
}

int		ft_count_index(char const *s, char c)
{
	unsigned int	index;

	index = 0;
	while (*s)
	{
		if (*s != c && *s != '\0' && (*(s + 1) == c || *(s + 1) == '\0'))
			index++;
		s++;
	}
	return (index);
}

int		ft_malloc_index(char **tab, char const *s, char c, unsigned int index)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(tab[index] = malloc(sizeof(char) * (i + 1))))
	{
		i = 0;
		while (i < index)
			free(tab[i++]);
		free(tab);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char				**tab;
	unsigned int		i;
	unsigned int		index;
	unsigned int		words;

	index = 0;
	if (!s || !(tab = malloc(sizeof(char *) * (ft_count_index(s, c) + 1))))
		return (NULL);
	words = ft_count_index(s, c);
	while (*s && index < words)
	{
		while (*s && *s == c)
			s++;
		if (!ft_malloc_index(tab, s, c, index))
			return (NULL);
		i = 0;
		while (*s && *s != c)
			tab[index][i++] = *s++;
		tab[index++][i] = '\0';
	}
	tab[index] = 0;
	return (tab);
}


// int main(int ac, char **av)
// {
// 	(void)ac;
// 	char	**tab;
// 	int		i;

// 	tab = ft_split(av[1], ' ');
// 	i = 0;
// 	printf("tab size %d\n", ft_get_tab_size(tab));
// 	while (tab[i])
// 		printf("%s\n", tab[i++]);
// 	ft_free_tab(tab);
// 	return (0);
// }
