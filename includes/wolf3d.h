/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vprypesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 15:45:57 by vprypesh          #+#    #+#             */
/*   Updated: 2018/09/12 15:45:58 by vprypesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define LEAK system("leaks wolf3d")
# define WIN_WIDTH 800
# define WIN_HEIGHT 800
# define BUFLEN 4096
# define ZERO 1e-6
# define PI 3.14
# define GRID 64
# define WALL 64
# define BMP_H 64
# define PLAYER 32
# define FOV 35 * PI / 180
# define UP 1
# define DOWN 0
# define LEFT 1
# define RIGHT 0
# define X 322
# define MAX_SIZE 100
# define MP3_MUSIC "./resources/sound/discovery.mp3"
# define WAV_STEP "./resources/sound/footstep.wav"
# include "../libft/libft.h"
# include "../includes/SDL/SDL2.framework/Headers/SDL.h"
# include "../includes/SDL/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../includes/SDL/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>

typedef struct		s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double move_speed;
	double rot_speed;
	double height;
	double view_ang;
}					t_player;

typedef struct		s_coords
{
	double	x;
	double	y;
	double	z;
}					t_coords;

typedef struct		s_draw_line
{
	t_coords	coords;
	double		k;
	double		d;
	double		x;
	double		b;
}					t_dln;

typedef struct		s_param
{
	TTF_Font		*font;
	Uint32			startclock;
	void			*mlx;
	void			*win;
	SDL_Renderer	*renderer;
	SDL_Surface		*img;
	SDL_Surface		*bmp;
	SDL_Surface		*north;
	SDL_Surface		*west;
	SDL_Surface		*south;
	SDL_Surface		*east;
	SDL_Surface		*floor;
	SDL_Surface		*sky;
	int				dst;
	char			*file;
	int				**map;
	double			color;
	t_player		player;
	int				side;
	double			ms;
	double			ang;
	int				left;
	int				d;
	double			ray_dir_x;
	double			ray_dir_y;
	double			perp_wall_dist;
	int				draw_start;
	int				draw_end;
	int				line_height;
	int				cast_type;
	t_coords		a;
	t_coords		b;
	int				fps;
	int				m_width;
	int				m_height;
	int				speedup;
	int				game;
	int				time;
	Uint32			lastframe;
	Uint32			start;
	double			tex_y;
	double			tex_x;
	double			floor_x_wall;
	double			floor_y_wall;
	double			wall_x;
	double			camera_x;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	double			delta_dist_x;
	double			delta_dist_y;
	int				map_x;
	int				map_y;
	double			weight;
	double			cur_floor_x;
	double			cur_floor_y;
	int				*res;
	Mix_Chunk		*sample;
}					t_params;
void				init_music(char *path, int mode);
void				play_step_sound(t_params *m, int loop);
void				key_system(SDL_Event e, t_params *m);
char				*parse_map(char *file_name);
void				render_text(t_params *m, char *str);
void				generate_mmap(t_params *m);
int					draw_until(int x, int y0, int y1, t_params *m);
int					draw_line(t_coords pos1, t_coords pos2, t_params *p);
double				texture_mapping2(t_params *m, int height, int line_height);
double				texture_mapping(t_params *m, double x, double y);
void				*create_image(t_params *m);
int					img_put_pixel(t_params *m, int x, int y, int color);
int					clear_img(t_params *m);
char				*get_text(char *file_name);
int					**str_to_int(char **file, t_params *m);
int					get_next_value(char **file, int row, int value);
int					count_width(char *str);
int					count_heigth(char **matrix);
void				cast(t_params *m);
void				test(t_params *m);
Uint32				get_color(t_params *m, int x, int y);
void				free_arr(int **arr, int height);
int					check_map(char *str);
void				cast_on_floor(int x, t_params *m);
int					check_fist_n_last(int **digits, t_params *m);
int					valid_format(char *file_name);
int					spawn_player(t_params *m);
void				clear_arr(char **str);

#endif
