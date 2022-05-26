#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void
print_usage(void)
{
    printf("\n\nA única linha de entrada consiste em um inteiro, que será o "
           "número inicial\n\n");
}

int
main(void)
{
    int n = 0;

    print_usage();

    scanf("%d", &n);

    /* respeita limite dado no enunciado */
    if (errno == ERANGE || (n < 1 || n > 1E6)) {
        perror("'n' deve estar dentro do intervalo: 1 <= n <= 10^6");
        return EXIT_FAILURE;
    }

    /* Aqui é utilizado o 'comma operator' para printar o número primeiro,
     *      para então checar a condição do laço */
    while (printf("%d", n), n > 1) {
        if (n % 2 == 0)
            n /= 2;
        else
            n = n * 3 + 1;
        putchar(' ');
    }
    putchar('\n');

    return EXIT_SUCCESS;
}
