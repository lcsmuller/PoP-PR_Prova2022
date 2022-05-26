#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void
print_usage(void)
{
    printf("\n\n* A entrada consiste de vários grupos A, B e C.\n"
           "* O programa será encerrado quando A e B forem 0.\n\n");
}

int
main(void)
{
    char buf[1024];
    int a, b;

    print_usage();

    while (1) {
        /* lê primeira linha contendo A e B */
        fgets(buf, sizeof(buf), stdin);
        if (sscanf(buf, "%d %d", &a, &b) != 2) {
            break;
        }
        /* encerra programa se A e B forem zero */
        if (a == 0 && b == 0) return EXIT_SUCCESS;

        /* lê segunda linha contendo C */
        fgets(buf, sizeof(buf), stdin);

        /* remove os menores valores, substituindo-os pelos elementos à sua
         * direita */
        int next_min_idx = 0;
        for (int i = 0; i < b; ++i) {
            /* 'min_idx' e 'j' irão sempre começar a partir do próximo menor
             *      valor conhecido salvo, a fim de economizar iterações. */
            int min_idx = next_min_idx;
            for (int j = min_idx + 1; j < a - i; ++j) {
                if (buf[j] < buf[min_idx]) {
                    next_min_idx = min_idx; // atualiza próximo menor valor conhecido
                    min_idx = j; // atualiza menor valor atual
                }
            }
            /* remove menor valor, movendo todos elementos à sua direita uma
             * casa para esquerda */
            memmove(buf + min_idx, buf + min_idx + 1, a - min_idx);
        }

        /* imprime maiores elementos que permaneceram */
        for (int i = 0; i < a - b; ++i)
            putchar(buf[i]);
        putchar('\n');
    }

    return EXIT_FAILURE;
}
