#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef	struct
{
	char	**map;
	int width;
	int	height;
	char	empty;
	char	obstacle;
	char	full;
}	Map;