#include <stdio.h>
#include <stdlib.h>

static void
print_usage(void)
{
    printf("\n\n* Primeira linha contém um inteiro N que é a quantidade de "
           "quedas.\n"
           "* As n linhas seguintes contém pares de valores com o instante de "
           "tempo de queda e o instante de tempo de retorno de um host, esses "
           "valores são do tipo inteiro.\n\n");
}

/* ordena instante do tempo de queda por ordem crescente */
static int
leftcmp(const void *a, const void *b)
{
    return (*(int(*)[2])a)[0] - (*(int(*)[2])b)[0];
}

/* ordena instante do tempo de retorno por ordem decrescente */
static int
rightcmp(const void *a, const void *b)
{
    return (*(int(*)[2])b)[1] - (*(int(*)[2])a)[1];
}

int
main(void)
{
    char buf[1024];
    int max_hosts = 0; // qtd max de hosts sem conexão ao mesmo tempo
    int n = 0;         // qtd de pares com o intervalo de instantes

    print_usage();

    /* obtem qtd de pares de instantes */
    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &n);
    if (n < 1 || n > 2 * 1E5) {
        fprintf(stderr, "Limite de N esperado: 1 <= n <= 2*10^5");
        return EXIT_FAILURE;
    }

    /* obtêm intervalos de instantes */
    int intervals[n][2]; // 0: instante de queda; 1: instante de retorno
    for (int i = 0; i < n; ++i) {
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d %d", &intervals[i][0], &intervals[i][1]) != 2) {
            return EXIT_FAILURE;
        }
    }

    /* Ordena pares por ordem de maiores intervalos, para isso é efetuado sort
     *      duas vezes, a primeira para ordenar os pontos da esquerda em ordem
     *      crescente, a segunda para ordenar os pontos da direita em ordem
     *      decrescente */
    qsort(intervals, n, sizeof(int[2]), leftcmp);
    qsort(intervals, n, sizeof(int[2]), rightcmp);

    /**
     * Compara cada par com seus sucessores, e incrementa 'nhosts' se o seu
     *      sucessor pertencer ao intervalo do par corrente. 
     *      A próxima iteração deverá começar do par seguinte ao corrente.
     */
    for (int i = 0; i < n; ++i) {
        int(*curr)[2] = &intervals[i]; // intervalo corrente
        int nhosts = 1;                // 1 é a qtd mínima possível de hosts

        for (int j = i + 1; j < n; ++j) {
            if ((*curr)[0] < intervals[j][1] && intervals[j][1] < (*curr)[1])
                ++nhosts;
        }
        if (nhosts > max_hosts) max_hosts = nhosts;
    }
    printf("%d\n", max_hosts);

    return EXIT_SUCCESS;
}
