#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **ag)
{
	//definimos w.h.iter, board, next, x, y, pen
	if (ac != 4)
		return 0;
	int w = atoi(ag[1]);
	int h = atoi(ag[2]);
	int iter = atoi(ag[3]);

	char c;
	int board[h][g];
	int next[h][g];
	int x = 0, y = 0, pen = 0;
	//inicializamos
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			board[i][j] = 0;
	//dibujo del mapa
	while(read(0, &c, 1) == 1)
	{
		if (c == 'w' && y > 0) y--;
		if (c == 's' && y < h-1) y++;
		if (c == 'a' && x > 0) x--;
		if (c == 'd' && x < w-1) x++;
		if (c == 'x') pen = !pen;
		if (pen) board[x][y] = 1;
	}
	//simulacion
	for (int z = 0; z < iter; z++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int n = 0;
				for (int di = -1; di <= 1; di++)
				{
					for (int dj = -1; dj <= 1; dj++)
						if ((di | dj) && (i + di >= 0 && i+di < h && j+dj >= 0 && dj+j < w)
							n += board[i + di][j + dj]; 
				}
				next[i][j] = (board[i][j] && (n == 2 || n == 3) || (!board[i][j] && n == 3),
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				board[i][j] = next[i][j];
	}
	//print
	for (int i = 0; i < h; i++){
		for (int j = 0;j < w; j++)
			putchar(board[i][j] ? '0' : ' ');
		putchar('\n');
	}
	return 0;
}
