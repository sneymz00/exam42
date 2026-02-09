#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char **ag)
{
	if (ac != 4)
		return 0;
	int w = atoi(ag[1]), h = atoi(ag[2]), iter = atoi(ag[3]);
	
	char c;
	int x = 0, y = 0, pen = 0;
	int next[h][w];
	int board[h][w];
	
	//inicializamos
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			board[i][j] = 0;
	//dibujamos
	while (read(0, &c, 1) == 1)
	{
		if (c == 'w' && x > 0) x--;
		if (c == 's' && x < h - 1) x++;
		if (c == 'a' && y > 0) y--;
		if (c == 'd' && y < w - 1) y++;
		if (c == 'x') pen = !pen;
		if (pen) board[x][y] = 1;
	}

	//simulamos 
	for (int z = 0; z < iter; z++)
	{
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int res = 0;
				for (int di = -1; di <= 1; di++)
				{
					for (int dj = -1; dj <= 1; dj++)
					{
						if (di == 0 && dj == 0) continue;
						if ((di || dj) && i + di >= 0 && i + di < h && j + dj >= 0 && j + dj < w)
							res += board[i + di][j + dj];}
				}
				next[i][j] = (board[i][j] && (res == 2 || res == 3)) || (!board[i][j] && res == 3);
			}
		}
		for (int i = 0; i < h; i++)
			for (int j = 0; j < w; j++)
				board[i][j] = next[i][j];
	}
	for (int i = 0; i < h; i++){
        	for (int j = 0; j < w; j++)
			putchar(board[i][j] ? '0' : ' ');
		putchar('\n');
	}
	return 0;	
}
