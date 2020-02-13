/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaouhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:40:09 by dhaouhao          #+#    #+#             */
/*   Updated: 2020/02/13 02:10:09 by dhaouhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_error(const char *error)
{
	ft_putstr("Error\n");
	ft_putstr((char*)error);
	return (0);
}

int		is_file_exist(int fd, char *type)
{
	char		*buffer;
	const char	*cant_read;
	const char	*no_file;
	int			ret;

	cant_read = !ft_strcmp(type, ".cub") ? CANT_RD_CUB : CANT_RD_XPM;
	no_file = !ft_strcmp(type, ".cub") ? NO_CUB : NO_XPM;
	ret = 0;
	if (!(buffer = malloc(sizeof(char) * 2)))
		return (exit_error(cant_read));
	if (!(read(fd, buffer, 0) < 0))
		ret = 1;
	free(buffer);
	if (ret == 0)
		return (exit_error(no_file));
	return (ret);
}

int		check_map(t_game_cf *game_cf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game_cf->rows && (x = -1))
		while (++x < game_cf->cols)
			if (game_cf->map[0][x] != 1 ||
			game_cf->map[y][0] != 1 ||
			game_cf->map[game_cf->rows - 1][x] != 1 ||
			game_cf->map[y][game_cf->cols - 1] != 1 ||
			(game_cf->map[y][x] != 0 && game_cf->map[y][x] != 1 &&
			game_cf->map[y][x] != 2))
				return (exit_error(MAP_NOT_CORRECT));
	return (1);
}

int		get_player_coords(t_game_cf *game_cf)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game_cf->rows && (x = -1))
		while (++x < game_cf->cols)
			if (game_cf->map[y][x] == 21 || game_cf->map[y][x] == 30 ||
			game_cf->map[y][x] == 35 || game_cf->map[y][x] == 39)
			{
				if (game_cf->direction == -1)
				{
					game_cf->direction = (char)(game_cf->map[y][x] + 48);
					game_cf->position[0] = x + 1;
					game_cf->position[1] = y + 1;
					game_cf->map[y][x] = 0;
				}
				else
					return (exit_error(TOO_MUCH_PLAYERS));
			}
	if (game_cf->direction == -1)
		return (exit_error(CANT_FIND_PLAYER));
	return (1);
}

void	free_map(int ***map, int rows)
{
	int row;

	row = 0;
	while (row < rows)
			free((*map)[row++]);
	free((*map));
	(*map) = NULL;
}

void	free_cf(t_game_cf *game_cf)
{
	if (game_cf->NO != NULL)
		free(game_cf->NO);
	if (game_cf->SO != NULL)
		free(game_cf->SO);
	if (game_cf->WE != NULL)
		free(game_cf->WE);
	if (game_cf->EA != NULL)
		free(game_cf->EA);
	if (game_cf->S != NULL)
		free(game_cf->S);
	if (game_cf->map != NULL)
		free_map(&game_cf->map, game_cf->rows);
}

int		fill_map(int ***map, t_game_cf *game_cf, char *line)
{
	int	**map_tmp;
	int	n_row;
	int	n_col;

	n_row = -1;
	if (*map != NULL && ft_strlen(line) != game_cf->cols)
		return (exit_error(MAP_NOT_CORRECT));
	game_cf->cols = ft_strlen(line);
	map_tmp = *map;
	if (!(*map = malloc(sizeof(int*) * (game_cf->rows + 1))))
		return (exit_error(CANT_MALLOC_MAP));
	while (++n_row < game_cf->rows + 1)
		if (!((*map)[n_row] = malloc(sizeof(int) * (game_cf->cols))))
			return (exit_error(CANT_MALLOC_MAP));
	n_row = -1;
	while ((n_col = -1) && map_tmp != NULL && ++n_row < game_cf->rows)
		while (++n_col < game_cf->cols)
			(*map)[n_row][n_col] = map_tmp[n_row][n_col];
	while (++n_col < game_cf->cols && ((*line -= '0') || 1))
		(*map)[game_cf->rows][n_col] = (int)(*(line++));
	if (map_tmp != NULL)
		free_map(&map_tmp, game_cf->rows);
	game_cf->rows += 1;
	return (1);
}

int		set_color(t_game_cf *game_cf, char **split)
{
	char	**rgb;
	int		i;
	int		j;

	i = -1;
	rgb = ft_split(split[1], ',');
	if (ft_get_tab_size(rgb) == 3)
	{
		while (++i < 3 && (j = -1))
			while (rgb[i][++j])
				if (!ft_isdigit(rgb[i][j]))
				{
					ft_free_tab(rgb);
					return (exit_error(COLOR_PROBLEM));
				}
				else if (!ft_strcmp(split[0], "F"))
					game_cf->floor[j] = ft_atoi(rgb[j]);
				else if (!ft_strcmp(split[0], "C"))
					game_cf->ceiling[j] = ft_atoi(rgb[j]);
		ft_free_tab(rgb);
		return (1);
	}
	ft_free_tab(rgb);
	return (exit_error(COLOR_PROBLEM));
}

int		fill_texture(t_game_cf *game_cf, char **split)
{
	if (!ft_strcmp(split[0], "NO") && (game_cf->NO = ft_strdup(split[1])))
		return (1);
	else if (!ft_strcmp(split[0], "SO") && (game_cf->SO = ft_strdup(split[1])))
		return (1);
	else if (!ft_strcmp(split[0], "EA") && (game_cf->EA = ft_strdup(split[1])))
		return (1);
	else if (!ft_strcmp(split[0], "WE") && (game_cf->WE = ft_strdup(split[1])))
		return (1);
	else if (!ft_strcmp(split[0], "S") && (game_cf->S = ft_strdup(split[1])))
		return (1);
	else
		return (exit_error(TEXTURE_PROBLEM));
}

int		set_texture(t_game_cf *game_cf, char **split)
{
	char	*xpm;
	int		fd;

	xpm = ft_substr(split[1], ft_strlen(split[1]) - 4, ft_strlen(split[1]));
	if (!ft_strcmp(xpm, ".xpm"))
	{
		free(xpm);
		fd = open(split[1], O_RDONLY);
		if (!is_file_exist(fd, ".xpm") || !fill_texture(game_cf, split))
		{
			close(fd);
			return (0);
		}
		else
			return (1);
	}
	else
		return (exit_error(NOT_XPM));
	return (1);
}

int		set_resolution(t_game_cf *game_cf, char **split)
{
	int	i;

	i = -1;
	while (split[1][++i])
		if (!ft_isdigit(split[1][i]))
			return (exit_error(RESOLUTION_PROBLEM));
	if (ft_atoi(split[1]) > game_cf->width)
		game_cf->width = ft_atoi(split[1]);
	i = -1;
	while (split[2][++i])
		if (!ft_isdigit(split[2][i]))
			return (exit_error(RESOLUTION_PROBLEM));
	if (ft_atoi(split[2]) > game_cf->height)
		game_cf->height = ft_atoi(split[2]);
	return (1);
}

int		extract_data(char **split, t_game_cf *game_cf)
{
	if (ft_get_tab_size(split) == 3 && !ft_strcmp(*split, "R"))
		return (set_resolution(game_cf, split));
	else if (ft_get_tab_size(split) == 2 && (!ft_strcmp(*split, "NO") ||
	!ft_strcmp(*split, "SO") || !ft_strcmp(*split, "WE") ||
	!ft_strcmp(*split, "EA") || !ft_strcmp(*split, "S")))
		return (set_texture(game_cf, split));
	else if (ft_get_tab_size(split) == 2 && (
	!ft_strcmp(*split, "F") || !ft_strcmp(*split, "C")))
		return (set_color(game_cf, split));
	if (ft_get_tab_size(split) == 1 && (*split)[0] == '1')
		return (fill_map(&game_cf->map, game_cf, *split));
	else
		return (0);
}

void	init_cf(t_game_cf *game_cf)
{
	int	i;

	game_cf->map = NULL;
	game_cf->rows = 0;
	game_cf->cols = 0;
	game_cf->width = 700;
	game_cf->height = 480;
	game_cf->NO = NULL;
	game_cf->SO = NULL;
	game_cf->WE = NULL;
	game_cf->EA = NULL;
	game_cf->S = NULL;
	game_cf->direction = -1;
	i = 0;
	while (i < 3 && (game_cf->floor[i] = 0) && (game_cf->ceiling[i] = 0))
		i++;
	i = 0;
	while (i < 2 && (game_cf->position[i] = -1))
		i++;
}

void	free_line_n_split(char **line, char ***split)
{
	if (*split != NULL)
		ft_free_tab(*split);
	*split = NULL;
	free(*line);
	*line = NULL;
}

int		parse_file(int fd, t_game_cf *game_cf)
{
	char	*line;
	char	**split;
	int		ret;

	init_cf(game_cf);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		split = (ft_strlen(line) > 0) ? ft_split(line, ' ') : NULL;
		if (split != NULL && !extract_data(split, game_cf))
		{
			free_line_n_split(&line, &split);
			free_cf(game_cf);
			return (0);
		}
		free_line_n_split(&line, &split);
		if (ret == 0)
			break ;
	}
	if (ret == -1 || !get_player_coords(game_cf) || !check_map(game_cf))
	{
		free_cf(game_cf);
		return (0);
	}

/****************************check configs***********************************/
	printf("screen parameter :\n");
	printf("width	: %zu\n", game_cf->width);
	printf("height	: %zu\n\n", game_cf->height);

	printf("textures paths :\n");
	printf("NO	: %s\n", game_cf->NO);
	printf("SO	: %s\n", game_cf->SO);
	printf("WE	: %s\n", game_cf->WE);
	printf("EA	: %s\n", game_cf->EA);
	printf("S	: %s\n\n", game_cf->S);

	printf("colors parameters :\n");
	printf("floor	: rgb[%d, %d, %d]\n", game_cf->floor[0], game_cf->floor[1], game_cf->floor[2]);
	printf("ceiling	: rgb[%d, %d, %d]\n\n", game_cf->ceiling[0], game_cf->ceiling[1], game_cf->ceiling[2]);

	printf("tab dimensions :\n");
	printf("rows	: %d\n", game_cf->rows);
	printf("cols	: %d\n\n", game_cf->cols);

	int n_row = 0;
	int n_col = 0;
	while (game_cf->map != NULL && n_row < game_cf->rows)
	{
		while (n_col < game_cf->cols)
		{
			printf("%d ", game_cf->map[n_row][n_col]);
			n_col++;
		}
		printf("\n");
		n_col = 0;
		n_row++;
	}

	printf("\n");
	printf("player starting parameters :\n");
	printf("direction	: %c\n", game_cf->direction);
	printf("position[0] 'width'	: %d\n", game_cf->position[0]);
	printf("position[1] 'height'	: %d\n\n", game_cf->position[1]);

	free_cf(game_cf);
/****************************************************************************************/

	return (1);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*cub;
	t_game_cf	game_cf;
	char		*buffer;

	if (ac == 2)
	{
		cub = ft_substr(av[1], ft_strlen(av[1]) - 4, ft_strlen(av[1]));
		if (!ft_strcmp(cub, ".cub"))
		{
			free(cub);
			fd = open(av[1], O_RDONLY);
			if (!is_file_exist(fd, ".cub") || !parse_file(fd, &game_cf))
			{
				close(fd);
				return (0);
			}
			else
			{
				// start the game here
			}
		}
		else
			return(exit_error(NOT_CUB));
	}
	else //if (ac == 1)
		return(exit_error(NO_CUB));
	// else
	// 	return(exit_error(TOO_MUCH_ARGS));
	return (0);
}
