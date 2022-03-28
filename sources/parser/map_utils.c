#include <parser.h>
#include <string.h>

void	check(t_map *start)
{
	int	kek = 0;

	while (start->up)
		start = start->up;
	while (start)
	{
		int	i = 0;
		printf("number\t%d\n", kek);
		printf("string %s\n", start->str);
		while (i < start->count)
		{
			char *str = strndup(&start->str[start->interval[i][0]],
								modi(start->interval[i][1]) - start->interval[i][0]);
			printf("beg index %d\n", start->interval[i][0]);
			printf("end index %d\n", start->interval[i][1]);
			printf("str chip '%s'\n", str);
			free(str);
			i++;
		}
		printf("count\t%d\n", start->count);
		printf("len\t%d\n", start->len);
		printf("__________\n\n\n");
		start = start->down;
		kek++;
	}
}

static char	**getarr(int counter, t_map *start, int len)
{
	int		index;
	char	**ret;

	index = 0;
	ret = ft_calloc(counter + 1, sizeof (char *));
	if (!ret)
		err_msg(mem_error);
	while (index < counter)
	{
		ret[index] = ft_strndup(start->str, len);
		if (!ret[index])
			err_msg(mem_error);
		index++;
		start = start->down;
	}
	return (ret);
}

char	**real_array(t_map *start)
{
	int		len;
	int		counter;
	t_map	*temp;

	counter = 0;
	len = start->len;
	temp = start;
	while (temp)
	{
		counter++;
		if (len < temp->len)
			len = temp->len;
		temp = temp->down;
	}
	return (getarr(counter, start, len));
}

void	check_chips(t_map *line)
{
	int		left;
	int		right;
	int		flag;
	int		index;
	char	*str;

	index = 0;
	while (index < line->count)
	{
		flag = 0;
		if (line->interval[index][1] < 0)
			flag = 1;
		str = line->str;
		right = modi(line->interval[index][1]);
		left = line->interval[index][0];
		while (left < right)
		{
			if (str[left] == '0' && flag)
				err_msg(content_err);
			left++;
		}
		index++;
	}
}

void	destroy_map(t_map *start)
{
	t_map	*temp;
	int		index;

	while (start)
	{
		temp = start;
		start = start->down;
		index = 0;
		while (temp->interval[index])
			free(temp->interval[index++]);
		free(temp->interval);
		free(temp->str);
		free(temp);
	}
}

void	get_params(t_data *info)
{
	int	len;
	int	counter;

	counter = 0;
	len = (int)ft_strlen(info->map[counter]);
	while (info->map[counter])
	{
		if (len < (int)ft_strlen(info->map[counter]))
			len = (int)ft_strlen(info->map[counter]);
		counter++;
	}
	info->map_width = len;
	info->map_height = counter;
}
