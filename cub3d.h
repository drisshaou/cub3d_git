/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaouhao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:46:58 by dhaouhao          #+#    #+#             */
/*   Updated: 2020/02/13 02:10:24 by dhaouhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define CANT_RD_CUB "Can't read the .cub file\n"
# define CANT_RD_XPM "Can't read the .xpm file\n"
# define MAP_NOT_CORRECT "The map is not correct.\n"
# define TOO_MUCH_PLAYERS "Too much players on map.\n"
# define CANT_FIND_PLAYER "Can't find a player on map.\n"
# define CANT_MALLOC_MAP "Can,t allocate memory for map.\n"
# define NOT_XPM "File is not .xpm extension.\n"
# define NOT_CUB "File is not .cub extension.\n"
# define RESOLUTION_PROBLEM "Problem with resolution.\n"
# define NO_XPM "There is no .xpm file.\n"
# define NO_CUB "There is no .xpm file.\n"
// # define TOO_MUCH_ARGS "Too much arguments entry.\n"
# define TEXTURE_PROBLEM "There is a problem with a texture.\n"
# define COLOR_PROBLEM "There is a problem with RGB color.\n"


# include <stddef.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_game_cf
{
	int				**map;
	int				rows;
	int				cols;
	int				position[2];
	char			direction;
	size_t			width;
	size_t			height;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*S;
	int				floor[3];
	int				ceiling[3];
}				t_game_cf;

int				get_next_line(int fd, char **line);
int				ft_read_file(char **stock, int fd);
void			ft_fill_static(char **stock, char *buf);
int				ft_line_break(char *stock);


char			**ft_split(char const *s, char c);
int				ft_malloc_index(char **tab, char const *s, char c,
				unsigned int index);
int				ft_count_index(char const *s, char c);
void			ft_free_tab(char **tab);
int				ft_get_tab_size(char **tab);


size_t			ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
void			ft_putstr(char *s);
void			ft_putchar(char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *s);
int				ft_isdigit(int c);



int				exit_error(const char *error);
int				is_file_exist(int fd, char *type);
int				check_map(t_game_cf *game_cf);
int				get_player_coords(t_game_cf *game_cf);
void			free_cf(t_game_cf *game_cf);
void			free_map(int ***map, int rows);
int				fill_map(int ***map, t_game_cf *game_cf, char *line);
int				set_color(t_game_cf *game_cf, char **split);
int				fill_texture(t_game_cf *game_cf, char **split);
int				set_texture(t_game_cf *game_cf, char **split);
int				set_resolution(t_game_cf *game_cf, char **split);
int				extract_data(char **split, t_game_cf *game_cf);
void			init_cf(t_game_cf *game_cf);
void			free_line_n_split(char **line, char ***split);
int				parse_file(int fd, t_game_cf *game_cf);


#endif
