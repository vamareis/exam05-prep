#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
	int lines;
	int width;
	char	empty;
	char	obstacle;
	char	full;
	char	**map;
} Map;

void    bsq(char *argv);
