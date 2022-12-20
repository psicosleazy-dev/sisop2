#include	<pthread.h>
#include	<semaphore.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>

#define	N 4
#define	TRUE 1

int	buffer[N], in = 0, out = 0;
sem_t	vazio, cheio, EM;

void *produtor(void *arg) {

   while(TRUE) {
      //sleep(rand()%5); 

      sem_wait(&vazio);	
      sem_wait(&EM);	   
      buffer[in] = rand() % 100;
      printf("Produzindo buffer[%d] = %d\n", in, buffer[in]);
      in= (in+1) % N;
      sem_post(&EM);
      sem_post(&cheio);
	   
   }
}

// produtor nao pode entrar quando buffer estiver cheio

void *consumidor(void *arg) {

   while(TRUE) {
      //sleep(rand()%5); 

      sem_wait(&cheio);
      sem_wait(&EM);
      printf("Consumindo buffer[%d] = %d\n", out, buffer[out]);
      out = (out+1) % N;
      sem_post(&EM);
      sem_post(&vazio);
	   
   }
}

// consumidor nao pode entrar quando buffer estiver vazio

int main(int argc, char *argv[ ]) {
    pthread_t cons, prod;
    
    // mutex so deu certo quando nao tem sleep
    sem_init(&vazio, 0, N);
    sem_init(&cheio, 0, 0);
    sem_init(&EM, 0, 1); // somente 1 tera acesso por vez
	
    pthread_create(&prod, NULL, produtor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);
    
    pthread_exit(0);
}
