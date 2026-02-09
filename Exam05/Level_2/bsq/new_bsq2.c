#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	if (ac < 2)
		return 1;
	//Abrimos con fopen
	FILE *f = fopen(ag[1], "r");
	int rows, r, c;
	char empty, obs, full;
	//leemos la cabecera con el numero de filas, empty, obs, full
	if (fscanf(f, "%d %c %c %c\n", &rows, &empty, &obs, &full) != 4)
		return 0;

	//Creamos el mapa de caracteres y la matriz de números
	char **map = malloc(sizeof(char *) * rows);
	int  **dp = malloc(sizeof(int *) * rows);

	//Variables para guardar donde esta el cuadrado más grande
	int max_v = 0, max_r = 0, max_c = 0;

	// Leer el mapa y calcular el cuadrado al mismo tiempo
	for (r = 0; r < rows; r++)
	{
		map[r] = malloc(10000); //buffer de 100000
		fgets(map[r], 10000, f); // 

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
				if (r == 0 || c == 0)
					dp[r][c] = 1;
				else
					dp[r][c] = min(dp[r-1][c], dp[r][c-1], dp[r-1][c-1]) + 1;
				if (dp[r][c] > max_v)
				{
					max_v = dp[r][c];
					max_r = r;
					max_c = c;
				}
			}
		}
	}

	for (int i = 0; i < max_v; i++)
	{
    	for (int j = 0; j < max_v; j++)
    	{
        	map[max_r - i][max_c - j] = full;
   		}	
	}

// 2. IMPRIMIR (Ahora que el mapa ya tiene el cuadrado pintado)
	for (r = 0; r < rows; r++)
	{
		printf("%s", map[r]);
	}
	return 0;
}