#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef    struct
{
    int lines;
    int width;
    char    empty;
    char    obstacle;
    char    full;
    char    **map;
}   Map;