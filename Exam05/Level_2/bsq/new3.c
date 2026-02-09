#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return a;
	if (b <= a && b <= c)
		return b;
	return c;
}

int main(int ac, char **ag)
{
	if (ac != 2)
		return 0;
	FILE *f = fopen(ag[1], "r");
	if (!f)
		return 0;
	char full, empty, obs;
	int c, r, rows);
	
	if (fscanf(f, "%d %c %c %c\n", &rows, &empty, &obs, &full) != 4)
		return 0;
	char **map = malloc(sizeof(char *) * rows);
	int **dp = malloc(sizeof(int *) * rows);

	int max_v = 0, max_r = 0, max_c = 0;
	for (r = 0; r < rows; r++)
	{
		map[r] = malloc(10000);
		fgets(map, 10000, f);
		static int cols = 0;
		if (cols == 0)
		{
			while (map[0][cols] && map[0][cols] != '\n')
				cols++;
		}
		dp[r] = malloc(sizeof(int) * cols);
		for (c = 0; c < cols; c++)
		{
			if (map[r][c] == obs)
				dp[r][c] = 0;
			else
			{
				if (c == 0 || r == 0)
					dp[r][c] = 1;
				else
					dp[r][c] = min(dp[r - 1][c], dp[r][c - 1], dp[r - 1][c - 1] + 1;
				if (dp[r][c] > max_v)
				{
					max_v = dp[r][c];
					max_c = c;
					max_r = r;
				}
			}
		}
	}	
	
	for (int i = 0; i < max_v; i++)
		for (int j = 0; j < max_v; j++)
			map[max_r - i][max_c - j] = full;

	for (r = 0; r < rows; r++)
		printf("%s", map[r]);
	return 0;
}
