#include "bsq.h"

void    free_map(Map *map)
{
    int i = -1;
    while (map->map[++i])
        free(map->map[i]);
    free(map->map);
    free(map);
}

void    print_map(char **map)
{
    int i = -1;
    while (map[++i])
        fprintf(stdout, "%s\n", map[i]);
}

int min3(int a, int b, int c)
{
    if (a < b && a < c)
        return (a);
    if (b < a && b < c)
        return (b);
    return (c);
}

Map*    get_map(char *argv)
{
    Map *map = malloc(sizeof(Map));
    char    *line;
    size_t  buf_size = 0;
    size_t  len = 0;

    FILE    *file = argv ? fopen(argv, "r") : stdin;
    if (file == NULL)
        return (free(map), NULL);
    
    if (fscanf(file, "%d %c %c %c\n", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
        return (fclose(file), free(map), NULL);

    map->map = calloc(map->lines + 1, sizeof(char *));
    for (int i = 0; i < map->lines; i++)
    {
        line = NULL;
        len = getline(&line, &buf_size, file);
        if (line[len - 1] != '\n')
            return (fclose(file), free(line), free_map(map), NULL);
        line[len - 1] = '\0';
        if (i == 0)
            map->width = strlen(line);
        else if ((int)strlen(line) != map->width)
            return (fclose(file), free(line), free_map(map), NULL);
        map->map[i] = line;
    }
    return (fclose(file), map);
}

bool    validate_map(Map *map)
{
    if (!map)
        return (false);
    if (map->lines < 1 || map->width < 1)
        return (free_map(map), false);
    if (map->empty == map->full || map->empty == map->obstacle || map->full == map->obstacle)
        return (free_map(map), false);
    if (!isprint(map->empty) || !isprint(map->full) || !isprint(map->obstacle))
        return (free_map(map), false);

    for (int i = 0; i < map->lines; i++)
        for (int j = 0; j < map->width; j++)
            if (map->map[i][j] != map->empty && map->map[i][j] != map->obstacle)
                return (free_map(map), false);
    
    return (true);
}

Map*    bsq_solver(Map *map)
{
    int **int_map = calloc(map->lines, sizeof(int*));
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
            else if(i == 0 || j == 0)
                int_map[i][j] = 1;
            else
                int_map[i][j] = min3(int_map[i - 1][j], int_map[i][j - 1], int_map[i - 1][j - 1]) + 1;

            if (int_map[i][j] > max_size)
            {
                if (i > 0 && j > 0 && int_map[i - 1][j] == int_map[i][j] - 1 &&
                     int_map[i][j - 1] == int_map[i][j] - 1 && 
                     int_map[i - 1][j - 1] == int_map[i][j] - 1)
                {
                    max_size = int_map[i][j];
                    best_i = i;
                    best_j = j;
                }
                else if (i == 0 || j == 0)
                     max_size = int_map[i][j];
            }
            /* printf("%d", int_map[i][j]); */
        }
        /* printf("\n"); */
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

int    bsq(char *argv)
{
    Map *map = get_map(argv);
    if (!validate_map(map))
        return (fprintf(stderr, "map error\n"), 1);
    map = bsq_solver(map);
    print_map(map->map);
    free_map(map);
    return (0);
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