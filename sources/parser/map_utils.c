#include <parser.h>

static int	count(char *str, int *index)
{
	int	ind;
	int	counter;

	counter = 1;
	while (str[*index] != '1')
	{
		if (str[*index] != ' ')
			err_msg(content_err);
		(*index)++;
	}
	ind = *index;
	while (str[ind])
	{
		while (str[ind] == '1')
			ind++;
		if (str[ind])
			counter++;
		while (str[ind] != '1' && str[ind])
		{
			if (!ft_strchr("0 NEWS", str[ind]))
				err_msg(content_err);
			ind++;
		}
	}
	return (counter);
}

static void	cycle(t_map *map, int index, int start, char *str)
{
	static int	counter = 0;
	int			index1;

	index1 = 0;
	map->interval[counter] = malloc(sizeof (int) * 2);
	if (!map->interval[counter])
		err_msg(mem_error);
	while (index > 0 && start + index1 < index)
	{
		if (str[start + index1] == ' ')
			index *= -1;
		index1++;
	}
	map->interval[counter][0] = start;
	map->interval[counter][1] = index;
	if (index > 0 && ft_strlen(str) == index - start)
		map->begin = -1;
	counter++;
}

static void	x_dim(char *str, t_map *map)
{
	int	index;
	int	counter;
	int	start;

	index = 0;
	start = 0;
	counter = count(str, &index);
	map->interval = ft_calloc((counter + 1), sizeof (int *));
	if (!map->interval)
		err_msg(mem_error);
	while (str[index])
	{
		cycle(map, index, start, str);
		while (str[index] == '1')
			index++;
		start = index;
		while (str[index] != '1' && str[index])
			index++;
	}
	cycle(map, index, start, str);
}

t_map	*new_nod(t_map *up, t_map *down, char *str, int begin)
{
	t_map	*ret;

	if (!str)
		return (NULL);
	ret = malloc(sizeof (*ret));
	if (!ret)
		err_msg(mem_error);
	if (!up)
		ret->up = NULL;
	else
		ret->up = up;
	if (!down)
		ret->down = NULL;
	else
		ret->down = down;
	if (begin)
		ret->begin = begin;
	else
		ret->begin = 0;
	x_dim(str, ret);
	return (ret);
}
