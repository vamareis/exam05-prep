#include "life.h"

void	free_board(char **board)
{
	int	i = -1;

	while(board[++i])
		free(board[i]);
	free(board);
}

void	print_board(char **board)
{
	int	i = -1;
	int	j;

	while (board[++i])
	{
		j = -1;
		while (board[i][++j])
			putchar(board[i][j]);
		putchar('\n');
	}
}

char    **new_board(int width, int height)
{
	char	**new = (char **)calloc(height + 1, sizeof(char *));

	for (int i = 0; i < height; i++)
	{
		new[i] = calloc(width + 1, sizeof(char));
		for (int j = 0; j < width; j++)
			new[i][j] = ' ';
	}
	return (new);
}

char	**populate_board(char **new, int width, int height)
{
	char    buf;
	int	index = 0;
	int	array = 0;
	bool	writing = false;

	while (read(0, &buf, 1) > 0)
	{
		if (buf == 'w' && array - 1 >= 0)
			array -= 1;
		else if (buf == 's' && array + 1 <= height - 1)
			array += 1;
		else if (buf == 'a' && index - 1 >= 0)
			index -= 1;
		else if (buf == 'd' && index + 1 <= width - 1)
			index += 1;
		else if (buf == 'x')
			writing = !writing;
		if (writing)
			new[array][index] = '0';
	}
	return (new);
}
	
char	**update_board(char **board, int width, int height)
{
	char	**new = new_board(width, height);
	int	index;
	int	cell_count;
	int	left;
	int	right;
	int	array = -1;
	
	while (++array < height)
	{
		index = -1;
		while (++index < width)
		{
			left = index - 1;
			if (left < 0)
				left = index;
			right = index + 1;
			if (right >= width)
				right = index;

			cell_count = 0;
			if (left != index && board[array][left] == '0')
				cell_count++;
			if (right != index && board[array][right] == '0')
				cell_count++;
			if (array > 0)
			{
				if (left != index && board[array - 1][left] == '0')
					cell_count++;
				if (right != index && board[array - 1][right] == '0')
					cell_count++;
				if (board[array - 1][index] == '0')
					cell_count++;
			}
			if (array < height - 1)
			{
				if (left != index && board[array + 1][left] == '0')
					cell_count++;
				if (right != index && board[array + 1][right] == '0')
					cell_count++;
				if (board[array + 1][index] == '0')
					cell_count++;
			}
			if ((cell_count == 2 || cell_count == 3) && board[array][index] == '0')
				new[array][index] = '0';
			if (cell_count == 3 && board[array][index] == ' ')
				new[array][index] = '0';
		}
	}
	free_board(board);
	return (new);
}

void    game_of_life(int width, int height, int iterations)
{
	char    **board;

	board = new_board(width, height);
	board = populate_board(board, width, height);
	for (int i = 0; i < iterations; i++)
		board = update_board(board, width, height);
	print_board(board);	
	free_board(board);
}