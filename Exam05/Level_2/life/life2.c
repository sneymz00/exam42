#include <stdlib.h>
#include <unistd.h>

// Si no quieres incluir stdio.h, puedes usar write para imprimir
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int main(int argc, char **argv) {
    if (argc != 4)
        return (0);

    int w = atoi(argv[1]);
    int h = atoi(argv[2]);
    int iter = atoi(argv[3]);
    
    // VALIDACIÓN IMPORTANTE: Prevenir mallocs de tamaño 0 o negativo
    if (w <= 0 || h <= 0)
        return (0);

    // USAR MALLOC (HEAP) en lugar de VLA (STACK)
    // Usamos calloc para que se inicialice todo a 0 automáticamente
    int *board = calloc(w * h, sizeof(int));
    int *next = malloc(w * h * sizeof(int));
    
    if (!board || !next) // Siempre comprobar si malloc falló
        return (0);

    int x = 0, y = 0, pen = 0;
    char c;
    
    // Draw
    while (read(0, &c, 1) == 1) {
        if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < h-1) y++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'd' && x < w-1) x++;
        else if (c == 'x') pen = !pen;
        
        if (pen) 
            board[y * w + x] = 1; // Acceso a array 1D
    }
    
    // Simulate
    for (int t = 0; t < iter; t++) {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int n = 0;
                // Lógica de vecinos
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        if (i+di >= 0 && i+di < h && j+dj >= 0 && j+dj < w)
                            n += board[(i+di) * w + (j+dj)];
                    }
                }
                
                // Reglas condensadas:
                // Viva (1) con 2 o 3 vecinos -> 1
                // Muerta (0) con 3 vecinos -> 1
                // Resto -> 0
                int current = board[i * w + j];
                if ((current == 1 && (n == 2 || n == 3)) || (current == 0 && n == 3))
                    next[i * w + j] = 1;
                else
                    next[i * w + j] = 0;
            }
        }
        // Copiar next a board
        for (int i = 0; i < h * w; i++)
            board[i] = next[i];
    }
    
    // Print
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            ft_putchar(board[i * w + j] ? '0' : ' ');
        ft_putchar('\n');
    }

    // LIBERAR MEMORIA
    free(board);
    free(next);
    
    return 0;
}