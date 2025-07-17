#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

typedef	struct
{
	int	lines;
	int	width;
	char	empty;
	char	obstacle;
	char	full;
	char	**map;
}	Map;