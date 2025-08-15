#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef	struct
{
	int	lines;
	int	width;
	char	empty;
	char	obstacle;
	char	full;
	char	**map;
}	Map;