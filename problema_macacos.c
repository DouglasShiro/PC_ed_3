/*
        UNIVERSIDADE DE BRASILIA
    Programação Concorrente 2/2016
           Estudo dirigido 3
         Problema dos macacos

    Douglas Shiro Yokoyama 13/0024902
*/

#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

#define MACA 50
#define MACB 50
#define DECIDIR 50 /*macaco vai ou fica no morro*/
#define TRUE 1
#define FALSE 0

pthread_mutex_t corda = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t decisao = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t turno = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int contA = MACA;
int contB = MACB;
int escolhaA;
int escolhaB;

void macaco_passandoA(int i);
void macaco_passandoB(int i);
void imprime_macaco();
void * macacoA(void * arg);
void * macacoB(void * arg);

int main(){
    pthread_t mA[MACA], mB[MACB];
    /*criando threads macacos*/
    int i;
    int *id;
    /*Macacos no morro A*/
    for(i = 0; i < MACA; i++){
        id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&mA[i], NULL, macacoA, (void*) (id));
    }
    /*Macacos no morro B*/
    for(i = 0; i < MACB; i++){
        id = (int*)malloc(sizeof(int));
        *id = i;
        pthread_create(&mB[i], NULL, macacoB, (void*) (id));
    }

    pthread_join(mA[0], NULL);

    return 0;
}

void * macacoA(void * arg){
    int i = *((int *) arg);

    while(TRUE){
        escolhaA = rand()%100;
        if(escolhaA < 50){
            escolhaA = 1;
        }else{
            escolhaA = 0;
        }
        pthread_mutex_lock(&turno);
        if(escolhaA && contA > 0){
            contA = contA - 1; /*macaco menos 1 que saiu do morro A*/
            contB = contB + 1; /*macaco mais 1 que passou para morro B*/
            pthread_mutex_lock(&corda);
        }

        macaco_passandoA(i);
        pthread_mutex_unlock(&turno);
        pthread_mutex_unlock(&corda);

    }
}

void * macacoB(void * arg){
    int i = *((int *) arg);

    while(TRUE){
        escolhaB = rand()%1;
        if(escolhaB < 50){
            escolhaB = 1;
        }else{
            escolhaB = 0;
        }
        pthread_mutex_lock(&turno);
        if(escolhaB && contB > 0){
            contB = contB - 1; /*macaco mais 1 que passou para morro B*/
            contA = contA + 1; /*macaco menos 1 que saiu do morro A*/
            pthread_mutex_lock(&corda);
        }
        macaco_passandoB(i);
        pthread_mutex_unlock(&turno);
        pthread_mutex_unlock(&corda);
    }
}

void macaco_passandoA(int i) {
    printf(" ~o    -------->    o/\n");
    printf("*A*                 *B*\n");
	printf("MacacoA %d esta passando para o outro morro\n", i);
    imprime_macaco();
    sleep(2);
}

void macaco_passandoB(int i) {
    printf(" o/    <--------    o~\n");
    printf("*A*                 *B*\n");
	printf("MacacoB %d esta passando para o outro morro\n", i);
    imprime_macaco();
    sleep(2);
}

void imprime_macaco(){
    printf("Numero de macacos\n Morro A: %d\n Morro B: %d\n", contA, contB);
}
