/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agigi <agigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 00:57:22 by agigi             #+#    #+#             */
/*   Updated: 2021/01/20 01:36:55 by agigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_resol_parser(char ** str, t_all *all)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (all->conf.res_x != -2 || all->conf.res_y != -2)
		ft_print_error("Resolution parameter is duplicated", 34);
	while (str[++i])
	{
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				ft_print_error("Incorrect resolution parameter", 30);
			j++;
		}
	}
	if ((all->conf.res_x = ft_atoi(str[1])) == -1)
		all->conf.res_x = MAX_RES_X;
	if ((all->conf.res_y = ft_atoi(str[2])) == -1)
		all->conf.res_y = MAX_RES_Y;
	if (all->conf.res_x <= 120 || all->conf.res_y <= 68)
	{
		all->conf.res_x = MIN_RES_X;
		all->conf.res_y = MIN_RES_Y;
	}
}

static void ft_rgb_parser_color(char **str, char **rgb, t_all *all)
{
	int c;

	if (str[0][0] == 'F')
	{
		if (all->conf.floor.flag != 1)
			ft_print_error("Floor parameter is duplicated", 29);
		else
		{
			if ((c = ft_check_rgb_range(rgb[0])))
				all->conf.floor.r = (unsigned char)c;
			if ((c = ft_check_rgb_range(rgb[1])))
				all->conf.floor.g = (unsigned char)c;
			if ((c = ft_check_rgb_range(rgb[2])))
				all->conf.floor.b = (unsigned char)c;
			all->conf.floor.flag = 0;
		}
	}
	else if (str[0][0] == 'C')
	{
		if (all->conf.ceiling.flag != 1)
			ft_print_error("Ceiling parameter is duplicated", 31);
		if ((c = ft_check_rgb_range(rgb[0])))
			all->conf.ceiling.r = (unsigned char)c;
		if ((c = ft_check_rgb_range(rgb[1])))
			all->conf.ceiling.g = (unsigned char)c;
		if ((c = ft_check_rgb_range(rgb[2])))
			all->conf.ceiling.b = (unsigned char)c;
		all->conf.ceiling.flag = 0;
	}
}

static void ft_rgb_parser(char **str, t_all *all)
{
	int i;
	int j;
	char **rgb;

	i = 0;
	j = 0;
	if (!(rgb = ft_split(str[1], ',')))
		ft_print_error("Failed to allocate memory", 25);
	while (rgb[i])
	{
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				ft_print_error("Incorrect color value", 21);
			j++;
		}
		i++;
	}
	if (i != 3)
		ft_print_error("Incorrect color value", 21);
	else
		ft_rgb_parser_color(str, rgb, all);
}

static void ft_check_params(char ** str, t_all *all, size_t len, size_t count)
{
	if (str[0][0] == 'R' && len == 1 && count == 3)
		ft_resol_parser(str, all);
	else if (str[0][0] == 'N' && str[0][1] == 'O' && len == 2 && count == 2 \
	&& ft_check_duplicate(all->conf.north))
		all->conf.north = ft_strdup(str[1]);
	else if (str[0][0] == 'S' && str[0][1] == 'O' && len == 2 && count == 2 \
	&& ft_check_duplicate(all->conf.south))
		all->conf.south = ft_strdup(str[1]);
	else if (str[0][0] == 'W' && str[0][1] == 'E' && len == 2 && count == 2 \
	&& ft_check_duplicate(all->conf.west))
		all->conf.west = ft_strdup(str[1]);
	else if (str[0][0] == 'E' && str[0][1] == 'A' && len == 2 && count == 2 \
	&& ft_check_duplicate(all->conf.east))
		all->conf.east = ft_strdup(str[1]);
	else if (str[0][0] == 'S' && len == 1 && count == 2 \
	&& ft_check_duplicate(all->conf.sprite))
		all->conf.sprite = ft_strdup(str[1]);
	else if ((str[0][0] == 'F' || str[0][0] == 'C') && len == 1 && count == 2)
		ft_rgb_parser(str, all);
	else
		ft_print_error("Incorrect parameter value", 25);
}

int ft_param_parser (char *line, t_all *all)
{
	char **str;
	size_t len;
	size_t count;

	count = 0;
	if (!ft_check_struct(all))
	{
		if (!(str = ft_split(line, ' ')))
			ft_print_error("Failed to allocate memory", 25);
		else if (str[0])
		{
			while(str[count])
				count++;
			len = ft_strlen(str[0]);
			ft_check_params(str, all, len, count);
		}
	}
	else
		ft_map_parser(line, all);

	return (0);
}
