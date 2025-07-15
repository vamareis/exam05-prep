#include "bsq.h"

void    print_map(char  **map)
{
    int i = -1;
    while(map[++i])
        fprintf(stdout, "%s\n", map[i]);
}

void    free_map(Map *map)
{
    int i = -1;
    while(map->map[++i])
        free(map->map[i]);
    free(map->map);
    free(map);
}

int min3(int a, int b, int c)
{
    if (a < b && a < c)
        return (a);
    else if (b < a && b < c)
        return (b);
    return (c);
}

bool    validate_map(Map *map)
{
    if (!map)
        return (false);
    if (map->lines < 1 || map->width < 1)
        return (free_map(map), false);
    if (map->empty == map->full || map->full == map->obstacle || map->empty == map->obstacle)
        return (free_map(map), false);
    if (!isprint(map->empty) || !isprint(map->full) || !isprint(map->obstacle))
        return (free_map(map), false);
    
    for (int i = 0; i < map->lines; i++)
        for (int j = 0; j < map->width; j++)
            if (map->map[i][j] != map->empty && map->map[i][j] != map->full && map->map[i][j] != map->obstacle)
                return (free_map(map), false);
    return (true);
}

Map*    get_map(char *argv)
{
    Map *map = malloc(sizeof(Map));
    size_t  size = 0;
    int len = 0;
    char    *line = NULL;
    
    FILE    *file = argv ? fopen(argv, "r") : stdin;

    if (fscanf(file, "%d %c %c %c\n", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
        return (fclose(file), NULL);
    
    map->map = calloc(map->lines + 1, sizeof(char *));
    for (int i = 0; i < map->lines; i++)
    {
        line = NULL;
        len = getline(&line, &size, file);
        if (line[len - 1] != '\n')
            return (fclose(file), free_map(map), free(line), NULL);
        line[len - 1] = '\0';
        if (i == 0)
            map->width = strlen(line);
        else if (map->width != (int)strlen(line))
            return (fclose(file), free_map(map), free(line), NULL);
        map->map[i] = line;
    }
    return (fclose(file), map);
}

Map*   solve_bsq(Map *map)
{
    int **int_map = malloc(map->lines * sizeof(int *));
    int max_size = 0;
    int best_i = 0;
    int best_j = 0;

    for (int i = 0; i < map->lines; i++)
    {
        int_map[i] = calloc(map->width, sizeof(int));
        for (int j = 0; j < map->width; j++)
        {
            if (map->map[i][j] == map->obstacle)
                int_map[i][j] = 0;
            else if (i == 0 || j == 0)
                int_map[i][j] = 1;
            else
                int_map[i][j] = min3(int_map[i][j - 1], int_map[i - 1][j], int_map[i - 1][j - 1]) + 1;

            if (int_map[i][j] > max_size)
            {
                max_size = int_map[i][j];
                best_i = i;
                best_j = j;
            }
        }
    }

    int start_i = best_i - max_size + 1;
    int start_j = best_j - max_size + 1;

    for (int i = start_i; i < start_i + max_size; i++)
        for (int j = start_j; j < start_j + max_size; j++)
            map->map[i][j] = map->full;

    for (int i = 0; i < map->lines; i++)
        free(int_map[i]);
    free(int_map);
    
    return (map);
}

void    bsq(char *argv)
{
    Map *map;

    map = get_map(argv);
    if (!validate_map(map))
    {
        fprintf(stderr, "map error\n");
        return ;
    }
    map = solve_bsq(map);
    print_map(map->map);
    free_map(map);
}

int main(int argc, char **argv)
{
    if (argc == 1)
        bsq(NULL);
    else
        for (int i = 1; i < argc; i++)
            bsq(argv[i]);
    return (0);
}