#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>

#include "metrorec.c"

atomic_int counter = 0;

void *passageiros_thread(void *arg)
{
    struct estacao *estacao = (struct estacao *) arg;
    estacao_espera_pelo_vagao(estacao);
    atomic_fetch_add(&counter, 1);
    return NULL;
}

struct vagao_args {
    struct estacao *estacao;
    int assentos_livres;
};

void *vagao_thread(void *args)
{
    struct vagao_args *vargs = (struct vagao_args *) args;
    estacao_preencher_vagao(vargs->estacao, vargs->assentos_livres);
    return NULL;
}

int run_test(int rand_passageiros, int rand_assentos)
{
    return 0;
}

int main(void)
{
    srand(time(NULL));
    int rand_passageiros = rand() % 100;

    struct estacao estacao;
    estacao_init(&estacao);

 printf("\n**************************************************\n");
 printf("*                ESTAÇÃO METROREC                *\n");
 printf("**************************************************\n");

    int passageiro = 0;
    pthread_t passageiros[rand_passageiros];

    for (int i = 0; i < rand_passageiros; i++) {
        pthread_create(&passageiros[i], NULL, passageiros_thread, &estacao);
        passageiro++;
    }

    printf("\n%d passageiros na estação...\n", passageiro);

    struct vagao_args vargs;
    vargs.estacao = &estacao;

    int repCount = 1;

    while (passageiro > 0) {
        int rand_assentos = rand() % 10;
        vargs.assentos_livres = rand_assentos;

        printf("\n%d passageiros na estação...\n", passageiro);

        int assentos = rand_assentos;

        pthread_t vagao;
        pthread_create(&vagao, NULL, vagao_thread, &vargs);
        printf("Vagão %d chegou na estação com %d assentos livres\n", repCount++, assentos);

        int reap;
        if (passageiro < assentos) {
            reap = passageiro;
        } else {
            reap = assentos;
        }

        while (reap != 0) {
            if (atomic_load(&counter) > 0) {
                passageiro--;
                assentos--;
                reap--;
                atomic_fetch_sub(&counter, 1);

                estacao_embarque(&estacao);
                printf("Um passageiro embarcou\n");
            }
        }

        if (atomic_load(&counter) > passageiro) {
            printf("Deu ruim\n");
            exit(0);
        }

        printf("Vagão saiu da estação com %d assentos vagos\n", assentos);
    }

    printf("\nEstação finalizada\n");
    printf("\nParece que está tudo certo.\n\n");
    return 0;
}