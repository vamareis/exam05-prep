#include "life.h"

void    print_map(char **map)
{
    int i = -1;
	int	j;
    while (map[++i])
	{
		j = -1;
		while(map[i][++j])
			putchar(map[i][j]);
		putchar('\n');
	}	
}

void	free_map(char **map)
{
	int	i = -1;
	while(map[++i])
		free(map[i]);
	free(map);
}

char    **map_creator(int width, int height)
{
    char    **map = calloc(height + 1, sizeof(char *));
    
    for (int i = 0; i < height; i++)
    {
        map[i] = calloc(width + 1, sizeof(char));
        for (int j = 0; j < width; j++)
            map[i][j] = ' ';
    }
    return (map);
}

char	**map_populator(char **map, int width, int height)
{
	char    buf;
    bool    writing = false;
	int line = 0;
    int col = 0;
    while (read(0, &buf, 1))
    {
        if (buf == 'w' && line > 0)
            line -= 1;
        else if (buf == 's' && line < height - 1)
            line += 1;
        else if (buf == 'a' && col > 0)
            col -= 1;
        else if (buf == 'd' && col < width - 1)
            col += 1;
        else if (buf == 'x')
		    writing = writing ? false : true;
		if (writing)
			map[line][col] = '0';
    }
    return (map);
}

char**	game_of_life(char **map, int width, int height)
{
	int	count;
	char	**new_map = map_creator(width, height);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			count = 0;
			if (map[i][j] == '0')
			{
				if (i > 0 && map[i - 1][j] == '0')
					count++;
				if (i > 0 && j > 0 && map[i - 1][j - 1] == '0')
					count++;
				if (i > 0 && j < width - 1 && map[i - 1][j + 1] == '0')
					count++;
				if (i < height - 1 && map[i + 1][j] == '0')
					count++;
				if (i < height - 1 && j > 0 && map[i + 1][j - 1] == '0')
					count++;
				if (i < height - 1 && j < width - 1 && map[i + 1][j + 1] == '0')
					count++;
				if (j > 0 && map[i][j - 1] == '0')
					count++;
				if (j < width - 1 && map[i][j + 1] == '0')
					count++;

				if (count == 2 || count == 3)
					new_map[i][j] = '0';
			}
			else if (map[i][j] == ' ')
			{
				if (i > 0 && map[i - 1][j] == '0')
					count++;
				if (i > 0 && j > 0 && map[i - 1][j - 1] == '0')
					count++;
				if (i > 0 && j < width - 1 && map[i - 1][j + 1] == '0')
					count++;
				if (i < height - 1 && map[i + 1][j] == '0')
					count++;
				if (i < height - 1 && j > 0 && map[i + 1][j - 1] == '0')
					count++;
				if (i < height - 1 && j < width - 1 && map[i + 1][j + 1] == '0')
					count++;
				if (j > 0 && map[i][j - 1] == '0')
					count++;
				if (j < width - 1 && map[i][j + 1] == '0')
					count++;
				
				if (count == 3)
					new_map[i][j] = '0';
			}
		}
	}
	free_map(map);
	return (new_map);
}

void    life(char **argv)
{
    char    **map;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    map = map_creator(width, height);
	map = map_populator(map, width, height);
    for (int i = 0; i < iterations; i++)
		map = game_of_life(map, width, height);
	print_map(map);
	free_map(map);
}

int main(int argc, char **argv)
{
    if (argc != 4)
        return (1);
    life(argv);
    return (0);
}