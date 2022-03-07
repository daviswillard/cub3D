
#include "../cub.h"

char	define_direct(t_data *data, double x, double y)
{
	double	next_up;
	double	next_down;
	double	next_right;
	double	next_left;
	char	direct;

	next_up = y - 0.01;
	next_down = y + 0.01;
	next_right = x + 0.01;
	next_left = x - 0.01;
	if (x < data->posx)
	{
		if (map[(int)next_up][(int)x] && map[(int)next_down][(int)x])
			direct = 'w';
		else if (map[(int)y][(int)next_right] == 0)
			direct = 'w';
		else
		{
			if (y < data->posy)
				direct = 'n';
			else
				direct = 's';
		}
	}
	else
	{
		if (map[(int)next_up][(int)x] && map[(int)next_down][(int)x])
			direct = 'e';
		else if (map[(int)y][(int)next_left] == 0)
			direct = 'e';
		else
		{
			if (y < data->posy)
				direct = 'n';
			else
				direct = 's';
		}
	}
	return (direct);
}

int	is_wall(t_data *data, double x, double y)
{
	if (map[(int)y][(int)x] == 1)
		return (1);
	else
		return (0);
}

void	cast_ray(t_data *data, double angle, int i)
{
	double	ray_len;
	double	x;
	double	y;

	x = data->posx;
	y = data->posy;
	ray_len = 0.0;
	while (!is_wall(data, x, y))
	{
		x = (float)data->posx + (ray_len * (sin(angle * M_PI / 180.0)));
		y = (float)data->posy - (ray_len * (cos(angle * M_PI / 180.0)));
		my_mlx_pixel_put(&data->image, x * 40.0, y * 40.0, 0x0000FFFF);
		ray_len += 0.01;
	}
	data->walls[i] = ray_len * cos(fabs(data->angle - angle) * M_PI / 180.0);
	data->direct[i] = define_direct(data, x, y);
	data->block_xpos[i] = x;
	data->block_ypos[i] = y;
	data->len[i] = ray_len;
	data->x_pos[i] = x;
	data->y_pos[i] = y;
	data->ang[i] = angle;
}

void	calculate_rays(t_data *data)
{
	float	angle;
	float	ratio;
	int		i;

	angle = data->angle - (RANGE / 2);
	ratio = (float)RANGE / (float)WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(data, angle, i);
		angle += ratio;
		i++;
	}
}
