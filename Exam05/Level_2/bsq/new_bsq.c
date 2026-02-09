#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int min(int a, int b, int c) {
    if (a <= b && a <= c)
		return a;
    if (b <= a && b <= c)
		return b;
    return c;;
}

int main(int ac, char **av) {
    // 1. Abrir archivo o usar stdin
    FILE *f = (ac > 1) ? fopen(av[1], "r") : stdin;
    int rows, r, c, max_v = 0, max_r = 0, max_c = 0;
    char empty, obs, full;

    // 2. Leer la cabecera (9 . o x)
    if (fscanf(f, "%d %c %c %c\n", &rows, &empty, &obs, &full) != 4) return 0;

    // 3. Crear matrices (usa memoria dinámica para evitar segfaults)
    char **map = malloc(sizeof(char *) * rows);
    int **dp = malloc(sizeof(int *) * rows);

    // 4. Leer el mapa y calcular el cuadrado al mismo tiempo
    for (r = 0; r < rows; r++) {
        map[r] = malloc(10000); // Un buffer suficientemente grande
        fgets(map[r], 10000, f);
        
        // Calcular el ancho (solo la primera vez)
        static int cols = 0;
        if (cols == 0) while (map[0][cols] && map[0][cols] != '\n') cols++;
        
        dp[r] = malloc(sizeof(int) * cols);
        for (c = 0; c < cols; c++) {
            if (map[r][c] == obs) dp[r][c] = 0;
            else {
                // Lógica de programación dinámica simplificada
                if (r == 0 || c == 0) dp[r][c] = 1;
                else {
                    int min = dp[r-1][c];
                    if (dp[r][c-1] < min) min = dp[r][c-1];
                    if (dp[r-1][c-1] < min) min = dp[r-1][c-1];
                    dp[r][c] = min + 1;
                }
                // Guardar el máximo
                if (dp[r][c] > max_v) {
                    max_v = dp[r][c]; max_r = r; max_c = c;
                }
            }
        }
    }

    // 5. Rellenar el cuadrado y mostrar el resultado
    for (r = 0; r < rows; r++) {
        for (int i = 0; i < max_v; i++)
            for (int j = 0; j < max_v; j++)
                map[max_r - i][max_c - j] = full;
        
        printf("%s", map[r]); // El \n ya viene en map[r] por el fgets
    }
    return 0;
}