//
//  main.c
//  Metodo Simplex
//
//  Created by Arilson Bolivar Ferreira on 21/08/23.
//

#include <stdio.h>
#include <locale.h>

#define MAX 10

void MetodoSimplex(int numeroDeEquacoes, int numeroDeVariaveis, float a[MAX][MAX], float b[MAX], float c[MAX], float z);

int main(int argc, const char * argv[]) {
    int i,j;
    int numeroDeEquacoes, numeroDeVariaveis;
    float a[MAX][MAX], b[MAX], c[MAX], z;
    
    setlocale(LC_ALL, "Portuguese");
    
    printf("---===| MÉTODO SIMPLEX |===---\n");
    
    printf("\nDigite o número de equações: ");
    
    scanf("%d", &numeroDeEquacoes);
    
    printf("\nDigite o número de variáveis: ");
    
    scanf("%d", &numeroDeVariaveis);
    
    printf("\nDigite os coeficientes da matriz A:\n");
    for (i = 0; i < numeroDeEquacoes; i++)
        for (j = 0; j < numeroDeVariaveis; j++)
            scanf("%f", &a[i][j]);

    
    printf("\nDigite os coeficientes da matriz B:\n");
    for (i = 0; i < numeroDeEquacoes; i++)
        scanf("%f", &b[i]);
    
    printf("\nDigite os coeficientes da matriz C:\n");
    for (j = 0; j < numeroDeVariaveis; j++)
        scanf("%f", &c[j]);
    
    printf("Digite o valor de Z: ");
        scanf("%f", &z);

        MetodoSimplex(numeroDeEquacoes, numeroDeVariaveis, a, b, c, z);
    
    return 0;
}

void MetodoSimplex(int numeroDeEquacoes, int numeroDeVariaveis, float a[MAX][MAX], float b[MAX], float c[MAX], float z) {
    int i, j;
    float min_ratio, min_value;
    int pivot_row = 0, pivot_col = 0;
    
    while (1) {
            min_value = 0;
            for (j = 0; j < numeroDeVariaveis; j++) {
                if (c[j] < min_value) {
                    min_value = c[j];
                    pivot_col = j;
                }
            }

            if (min_value >= 0)
                break;

            min_ratio = -1;
            for (i = 0; i < numeroDeEquacoes; i++) {
                if (a[i][pivot_col] > 0) {
                    if (min_ratio == -1 || b[i] / a[i][pivot_col] < min_ratio) {
                        min_ratio = b[i] / a[i][pivot_col];
                        pivot_row = i;
                    }
                }
            }

            if (min_ratio == -1) {
                printf("Solução ilimitada\n");
                return;
            }

            b[pivot_row] /= a[pivot_row][pivot_col];
            for (j = 0; j < numeroDeVariaveis; j++)
                if (j != pivot_col)
                    a[pivot_row][j] /= a[pivot_row][pivot_col];
            a[pivot_row][pivot_col] = 1;

            for (i = 0; i < numeroDeEquacoes; i++) {
                if (i != pivot_row) {
                    b[i] -= a[i][pivot_col] * b[pivot_row];
                    for (j = 0; j < numeroDeVariaveis; j++)
                        if (j != pivot_col)
                            a[i][j] -= a[i][pivot_col] * a[pivot_row][j];
                    a[i][pivot_col] = 0;
                }
            }

            z += c[pivot_col] * b[pivot_row];
            for (j = 0; j < numeroDeVariaveis; j++)
                if (j != pivot_col)
                    c[j] -= c[pivot_col] * a[pivot_row][j];
            c[pivot_col] = 0;
        }

        printf("Solução ótima encontrada\n\n");
        printf("Valor ótimo de Z: %f\n\n", z);

    
    return;
}
