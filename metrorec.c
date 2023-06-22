#include <pthread.h>

struct estacao {
    pthread_mutex_t mutex; 
    pthread_cond_t cond_vagao_chegou; 
    pthread_cond_t cond_passageiro_embarcou; 
    int passageiros_na_estacao; 
    int assentos_livres; 
};

void estacao_init(struct estacao *estacao) {
    estacao->passageiros_na_estacao = 0;  
    estacao->assentos_livres = 0; 
    pthread_mutex_init(&estacao->mutex, NULL); 
    pthread_cond_init(&estacao->cond_vagao_chegou, NULL); 
    pthread_cond_init(&estacao->cond_passageiro_embarcou, NULL); 
}

void estacao_preencher_vagao(struct estacao * estacao, int assentos) {
    pthread_mutex_lock(&estacao->mutex); 
    estacao->assentos_livres = assentos;
    pthread_cond_broadcast(&estacao->cond_vagao_chegou); 
    while (estacao->assentos_livres > 0) {
        pthread_cond_wait(&estacao->cond_passageiro_embarcou, &estacao->mutex); 
    } 
    pthread_mutex_unlock(&estacao->mutex); 
}

void estacao_espera_pelo_vagao(struct estacao * estacao) {
    pthread_mutex_lock(&estacao->mutex); 
    estacao->passageiros_na_estacao++;  
    while (estacao->assentos_livres == 0) {
        pthread_cond_wait(&estacao->cond_vagao_chegou, &estacao->mutex); 
    } 
    estacao->assentos_livres--; 
    pthread_mutex_unlock(&estacao->mutex); 
}

void estacao_embarque(struct estacao * estacao) {
    pthread_mutex_lock(&estacao->mutex);     
    estacao->passageiros_na_estacao--; 
    if (estacao->assentos_livres == 0 || estacao->passageiros_na_estacao == 0) {  
        pthread_cond_signal(&estacao->cond_passageiro_embarcou);    
    }
    pthread_mutex_unlock(&estacao->mutex);   
}