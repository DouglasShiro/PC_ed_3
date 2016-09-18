#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MACA 10
#define MACB 20
#define TRUE 1

pthread_mutex_t turno = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t corda = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_l = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_o = PTHREAD_MUTEX_INITIALIZER;

void * macacaA (void * arg);
void * macacoB (void * arg);

int morroA = MACA;
int morroB = MACB;

int main(){
    pthread_t mA[MACA], mB[MACB];

    srand(time(NULL));

    int i;
    int *id;

    for(i = 0; i < MACA; i++){
        id = (*int)malloc(sizeof(int));
        *id = i;
        pthread_create(&mA[i], NULL, macacoA, (void*) (id));
    }

    for(i = 0; i < MACB; i++){
        id = (*int)malloc(sizeof(int));
        *id = i;
        pthread_create(&mB[i], NULL, macacoB, (void*) (id));
    }

    pthread_join(mA[0], NULL);

return 0;
}

void * macacoA(void * arg){
    int i = *((int*) arg);
    int decisao = rand()%100;
    if(decisao < 50){
        decisao = 1;
    }else{
        decisao = 0;
    }
    pthread_mutex_lock(&turno);
    pthread_mutex_lock(&mutex_l);
    
}

void * macacoB(void * arg){
    int i = *((int*) arg);


}
