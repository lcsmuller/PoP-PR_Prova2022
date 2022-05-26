#include <stdio.h>
#include <stdlib.h>

static void
print_usage(void)
{
    printf("\n\n* Entre a quantidade N de strings a serem analisadas.\n"
           "* Entre as strings contendo os pares '<','>', e '.' dispostos "
           "aleatoriamente.\n\n");
}

int
main(void)
{
    char buf[1024]; // string de pares atual
    int n = 0;      // quantidade de strings de pares

    print_usage();

    fgets(buf, sizeof(buf), stdin);
    sscanf(buf, "%d", &n);

    while (n-- > 0) {
        int npairs = 0; // qtd de pares '<>' encontrados
        int depth = 0;  // "percorre" os pares '<>' pela sua profundidade

        /* lê linha contendo pares e parseia seus tokens */
        fgets(buf, sizeof(buf), stdin);
        for (int i = 0; buf[i]; ++i) {
            switch (buf[i]) {
            case '.':
            case '\n':
                break;
            case '<':
                ++depth;
                break;
            case '>':
                /* se o token '>' for encontrado e depth for diferente de 0
                 * então significa que existe algum '<' */
                if (depth > 0) {
                    --depth;
                    ++npairs;
                }
                break;
            default:
                fprintf(stderr, "Caractere inesperado: '%c'\n", buf[i]);
                return EXIT_FAILURE;
            }
        }
        printf("%d\n", npairs);
    }

    return EXIT_SUCCESS;
}
